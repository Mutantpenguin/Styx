#include "CFreeImageWrapper.hpp"

#include <physfs.h>

#include "src/engine/logger/CLogger.hpp"

bool CFreeImageWrapper::m_initialized = false;
FreeImageIO CFreeImageWrapper::m_io;

CFreeImageWrapper::CFreeImageWrapper()
{
}

CFreeImageWrapper::~CFreeImageWrapper()
{
}

FreeImageIO &CFreeImageWrapper::Get( const CFileSystem &p_filesystem )
{
	if( !m_initialized )
	{
		Initialize( p_filesystem );
	}
	return( m_io );
}

// p_filesystem is unused. we just need to be sure that the filesystem is already initialized. hence this parameter
void CFreeImageWrapper::Initialize( const CFileSystem & )
{
	m_initialized = true;

	logINFO( "FreeImage has version '{0}'", FreeImage_GetVersion() );

	// assign wrapper-functions so freeimage can use our own file-system and logging

	FreeImage_SetOutputMessage( []( FREE_IMAGE_FORMAT fif, const char *msg )
									{
										if( fif != FIF_UNKNOWN )
										{
											logWARNING( "{0} : {1}", FreeImage_GetFormatFromFIF( fif ), msg );
										}
										else
										{
											logWARNING( msg );
										}
									} );

	// TODO really need to get this sorted out, since it is a huge code duplication
	m_io.read_proc	=	[]( void *buffer, unsigned int objSize, unsigned int objCount, void *handle ) -> unsigned int
							{
								const PHYSFS_sint64 retval = PHYSFS_readBytes( static_cast< PHYSFS_file* >( handle ), buffer, static_cast< PHYSFS_uint64 >( objSize ) * static_cast< PHYSFS_uint64 >( objCount ) );
								return( ( retval <= 0 ) ? retval : ( retval / static_cast< PHYSFS_sint64 >( objSize ) ) );
							};

	m_io.write_proc	=	[]( void *buffer, unsigned int objSize, unsigned int objCount, void *handle ) -> unsigned int
							{
								const PHYSFS_sint64 retval = PHYSFS_writeBytes( static_cast< PHYSFS_file* >( handle ), buffer, static_cast< PHYSFS_uint64 >( objSize ) * static_cast< PHYSFS_uint64 >( objCount ) );
								return( ( retval <= 0 ) ? retval : ( retval / static_cast< PHYSFS_sint64 >( objSize ) ) );
							};

	m_io.seek_proc	=	[]( void *handle, long pos, int origin ) -> int
							{
								switch( origin )
								{
								case SEEK_SET	:	return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), pos ) );
								case SEEK_CUR	:	return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), PHYSFS_tell( static_cast< PHYSFS_file* >( handle ) ) + pos ) );
								case SEEK_END	:	return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), PHYSFS_fileLength( static_cast< PHYSFS_file* >( handle ) + pos ) ) );
								}

								return( false );
							};

	m_io.tell_proc	=	[]( void *handle ) -> long
							{
								return( PHYSFS_tell( static_cast< PHYSFS_file* >( handle ) ) );
							};

/* TODO
	io.read_proc = [=]( void *buffer, unsigned int objSize, unsigned int objCount, void *handle ) -> unsigned int
						{
							return( m_filesystem.Read( buffer, objSize, objCount, reinterpret_cast< CFileSystem::File* >( handle ) ) );
						};

	io.write_proc	= [=]( void *buffer, unsigned int objSize, unsigned int objCount, void *handle ) -> unsigned int
						{
							return( m_filesystem.Write( buffer, objSize, objCount, reinterpret_cast< CFileSystem::File* >( handle ) ) );
						};

	io.seek_proc	= [=]( void *handle, long pos, int origin ) -> int
						{
							return( m_filesystem.Seek( reinterpret_cast< CFileSystem::File* >( handle ), pos, origin ) );
						};

	io.tell_proc	= [=]( void *handle ) -> long
						{
							return( m_filesystem.Tell( reinterpret_cast< CFileSystem::File* >( handle ) ) );
						};
*/
}
