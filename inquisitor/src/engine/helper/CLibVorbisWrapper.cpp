#include "CLibVorbisWrapper.hpp"

#include <physfs.h>

#include "src/engine/logger/CLogger.hpp"

bool CLibVorbisWrapper::m_initialized = false;
ov_callbacks CLibVorbisWrapper::m_io;

CLibVorbisWrapper::CLibVorbisWrapper()
{
}

CLibVorbisWrapper::~CLibVorbisWrapper()
{
}

ov_callbacks &CLibVorbisWrapper::Get( const CFileSystem &p_filesystem )
{
	if( !m_initialized )
	{
		m_Initialize( p_filesystem );
	}
	return( m_io );
}

// p_filesystem is unused. we just need to be sure that the filesystem is already initialized. hence this parameter
void CLibVorbisWrapper::m_Initialize( const CFileSystem & )
{
	m_initialized = true;

	logDEBUG( "libvorbis has version '{0}'", vorbis_version_string() );

	// assign wrapper-functions so libvorbis can use our own file-system

	// TODO really need to get this sorted out, since it is a huge code duplication
	m_io.read_func 	=	[]( void *buffer, size_t objSize, size_t objCount, void *handle ) -> size_t
							{
								const PHYSFS_sint64 retval = PHYSFS_readBytes( static_cast< PHYSFS_file* >( handle ), buffer, static_cast< PHYSFS_uint64 >( objSize ) * static_cast< PHYSFS_uint64 >( objCount ) );
								return( ( retval <= 0 ) ? retval : ( retval / static_cast< PHYSFS_sint64 >( objSize ) ) );
							};

	m_io.seek_func	=	[]( void *handle, long pos, int origin ) -> int
							{
								switch( origin )
								{
								case SEEK_SET	:	return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), pos ) );
								case SEEK_CUR	:	return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), PHYSFS_tell( static_cast< PHYSFS_file* >( handle ) ) + pos ) );
								case SEEK_END	:	return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), PHYSFS_fileLength( static_cast< PHYSFS_file* >( handle ) + pos ) ) );
								}

								return( false );
							};

	m_io.tell_func	=	[]( void *handle ) -> long
							{
								return( PHYSFS_tell( static_cast< PHYSFS_file* >( handle ) ) );
							};

	m_io.close_func	=	[]( void *handle ) -> int
							{
								return( PHYSFS_close( static_cast< PHYSFS_file* >( handle ) ) );
							};

}
