#include "CFileSystem.hpp"

#include <physfs.h>

#include "src/engine/logger/CLogger.hpp"
#include "src/engine/logger/CLogTargetFile.hpp"


CFileSystem::CFileSystem( const char *argv0, const std::string &organisation, const std::string &gamename, const std::string &gamedir, const std::vector< std::string > &assets )
{
	PHYSFS_Version version_linked;
	PHYSFS_Version version_compiled;

	PHYSFS_getLinkedVersion( &version_linked );
	PHYSFS_VERSION( &version_compiled );

	logDEBUG( "PhysicsFS has version '{0}.{1}.{2}'", version_linked.major, version_linked.minor, version_linked.patch );

	if(	( version_compiled.major != version_linked.major )
		||
		( version_compiled.minor != version_linked.minor )
		||
		( version_compiled.patch != version_linked.patch ) )
	{
		logERROR( "\tbut version '{0}.{1}.{2}' was expected", PHYSFS_VER_MAJOR, PHYSFS_VER_MINOR, PHYSFS_VER_PATCH );
		throw Exception();
	}

	if( !PHYSFS_init( argv0 ) )
	{
		logERROR( "initializing PhysicsFS failed because of: {0}", PHYSFS_getLastError() );
		throw Exception();
	}

	// forbid symbolic links
	PHYSFS_permitSymbolicLinks( 0 );

	std::string prefsDir = PHYSFS_getPrefDir( organisation.c_str(), gamename.c_str() );
	if( prefsDir.empty() )
	{
		logERROR( "not possible to get prefs-directory because of: {0}", PHYSFS_getLastError() );
		throw Exception();
	}

	logDEBUG ( "prefs-directory is: {0}", prefsDir );

	if( !PHYSFS_setWriteDir( prefsDir.c_str() ) )
	{
		logERROR( "couldn't set write-dir to '{0}' because of: {1}", prefsDir, PHYSFS_getLastError() );
		throw Exception();
	}

	const std::string logDir( "log" );
	if( !PHYSFS_exists( logDir.c_str() ) )
	{
		if( !PHYSFS_mkdir( logDir.c_str() ) )
		{
			logERROR( "couldn't create log-directory '{0}' because of: {1}", logDir, PHYSFS_getLastError() );
			throw Exception();
		}
	}

	// pass an absolut path since CLogTargetFile doesn't use Physfs to write the log
	CLogger::CreateTarget< CLogTargetFile >( std::string( PHYSFS_getWriteDir() ) + std::string( PHYSFS_getDirSeparator() ) + logDir + std::string( PHYSFS_getDirSeparator() ) );

	// put write-dir first in search path
	if( !PHYSFS_mount( PHYSFS_getWriteDir(), nullptr, 0 ) )
	{
		logERROR( "adding '{0}' to search path failed because of: {1}", PHYSFS_getWriteDir(), PHYSFS_getLastError() );
		throw Exception();
	}

	// put asset-paths next in search path
	for( const std::string &asset : assets )
	{
		const std::string asset_path = gamedir + std::string( PHYSFS_getDirSeparator() ) + asset;

		logDEBUG( "adding asset-path '{0}'", asset_path );

		if( !PHYSFS_mount( asset_path.c_str(), nullptr, 1 ) )
		{
			logERROR( "adding asset-path '{0}' to search path failed because of: {1}", asset_path, PHYSFS_getLastError() );
			throw Exception();
		}
	}

	// put base dir last in search path
	if( !PHYSFS_mount( PHYSFS_getBaseDir(), nullptr, 1 ) )
	{
		logERROR( "adding '{0}' to search path failed because of: {1}", PHYSFS_getBaseDir(), PHYSFS_getLastError() );
		throw Exception();
	}

	InitialiseFreeImageIO();
}

CFileSystem::~CFileSystem( void )
{
	if( !PHYSFS_deinit() )
	{
		logWARNING( "deinitializing PhysicsFS failed because of: {0}", PHYSFS_getLastError() );
	}
}

bool CFileSystem::Exists( const std::string &filename ) const
{
	return( PHYSFS_exists( filename.c_str() ) );
}

bool CFileSystem::IsDirectory( const std::string &name ) const
{
	PHYSFS_Stat stat;
	PHYSFS_stat( name.c_str(), &stat );

	return( stat.filetype == PHYSFS_FILETYPE_DIRECTORY );
}

bool CFileSystem::IsEOF( File *handle ) const
{
	return( PHYSFS_eof( static_cast< PHYSFS_file* >( handle ) ) );
}

std::int64_t CFileSystem::GetLastModTime( const std::string &filename ) const
{
	PHYSFS_Stat stat;
	PHYSFS_stat( filename.c_str(), &stat );

	return( stat.modtime );
}

CFileSystem::File* CFileSystem::Open( const std::string &filename, e_openmode openmode ) const
{
	switch( openmode )
	{
		case e_openmode::READ :
			return( static_cast< File* >( PHYSFS_openRead( filename.c_str() ) ) );

		case e_openmode::WRITE :
			return( static_cast< File* >( PHYSFS_openWrite( filename.c_str() ) ) );

		case e_openmode::APPEND :
			return( static_cast< File* >( PHYSFS_openAppend( filename.c_str() ) ) );

		default:
			return( nullptr );
	}
}

void CFileSystem::Close( File *handle ) const
{
	PHYSFS_close( static_cast< PHYSFS_file* >( handle ) );
}

std::int64_t CFileSystem::Length( File *handle ) const
{
	return( PHYSFS_fileLength( static_cast< PHYSFS_file* >( handle ) ) );
}

std::string CFileSystem::GetWriteDir( void ) const
{
	return( std::string( PHYSFS_getWriteDir() ) );
}

bool CFileSystem::MakeDir( const std::string &dirname ) const
{
	return( PHYSFS_mkdir( dirname.c_str() ) );
}

const char* CFileSystem::GetLastError( void ) const
{
	return( PHYSFS_getLastError() );
}

std::string CFileSystem::LoadTextFileToBuffer( const std::string &filename ) const
{
	PHYSFS_file* temp_file = PHYSFS_openRead( filename.c_str() );

	const auto length = PHYSFS_fileLength( temp_file );

	std::string buffer;
	buffer.resize( length );

	PHYSFS_readBytes( temp_file, &buffer[ 0 ], length );

	PHYSFS_close( temp_file );

	return( buffer );
}

const char *CFileSystem::GetDirSeparator( void )
{
	return( PHYSFS_getDirSeparator() );
}

CFileSystem::FileBuffer CFileSystem::LoadFileToBuffer( const std::string &filename ) const
{
	if( !PHYSFS_exists( filename.c_str() ) )
	{
		logWARNING( "file '{0}' does not exist" );
		return {};
	}

	PHYSFS_file* f = PHYSFS_openRead( filename.c_str() );
	if( nullptr == f )
	{
		logWARNING( "file '{0}' couldn't be opened", filename );
		return {};
	}

	auto length = PHYSFS_fileLength( f );

	FileBuffer buffer( length );

	const auto lengthRead = PHYSFS_readBytes( f, &buffer[ 0 ], length );

	if( lengthRead != length )
	{
		logERROR( "couldn't read all of file '{0}' because of: {1}", filename, PHYSFS_getLastError() );
		return {};
	}

	PHYSFS_close( f );

	return( buffer );
}

bool CFileSystem::SaveBufferToFile( const FileBuffer &buffer, const std::string &filename ) const
{
	PHYSFS_file* f = PHYSFS_openWrite( filename.c_str() );

	if( nullptr == f )
	{
		logERROR( "File '{0}' couldn't be opened for writing because of: {1}", filename, PHYSFS_getLastError() );
		return( false );
	}

	const auto lengthWrite = PHYSFS_writeBytes( f, &buffer[ 0 ], buffer.size() );

	PHYSFS_close( f );

	if( lengthWrite != buffer.size() )
	{
		logERROR( "couldn't write all of file '{0}' because of: {1}", filename, PHYSFS_getLastError() );
		return( false );
	}

	return( true );
}

/*
std::int64_t CFileSystem::s_Read( void *buffer, std::size_t objSize, std::size_t objCount, File *handle )
{
	const PHYSFS_sint64 retval = PHYSFS_readBytes( static_cast< PHYSFS_file* >( handle ), buffer, static_cast< PHYSFS_uint64 >( objSize ) * static_cast< PHYSFS_uint64 >( objCount ) );

	return( ( retval <= 0 ) ? retval : ( retval / static_cast< PHYSFS_sint64 >( objSize ) ) );
}

std::int64_t CFileSystem::s_Write( void *buffer, std::size_t objSize, std::size_t objCount, File *handle )
{
	const PHYSFS_sint64 retval = PHYSFS_writeBytes( static_cast< PHYSFS_file* >( handle ), buffer, static_cast< PHYSFS_uint64 >( objSize ) * static_cast< PHYSFS_uint64 >( objCount ) );

	return( ( retval <= 0 ) ? retval : ( retval / static_cast< PHYSFS_sint64 >( objSize ) ) );
}

std::int32_t CFileSystem::s_Seek( File *handle, std::int64_t pos, std::int32_t whence )
{
	switch( whence )
	{
		case SEEK_SET :
			return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), pos ) );

		case SEEK_CUR :
			return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), PHYSFS_tell( static_cast< PHYSFS_file* >( handle ) ) + pos ) );

		case SEEK_END :
			return( PHYSFS_seek( static_cast< PHYSFS_file* >( handle ), PHYSFS_fileLength( static_cast< PHYSFS_file* >( handle ) + pos ) ) );
	}

	return( false );
}

std::int64_t CFileSystem::s_Tell( File *handle )
{
	return( PHYSFS_tell( static_cast< PHYSFS_file* >( handle ) ) );
}
*/

void CFileSystem::InitialiseFreeImageIO( void )
{
	/* TODO
	logINFO( "FreeImage has version '{0}'", FreeImage_GetVersion() );

	FreeImage_SetOutputMessage(	[]( FREE_IMAGE_FORMAT fif, const char *msg )
								{
									if( fif != FIF_UNKNOWN )
									{
										logWARNING( "{0}: {1}", FreeImage_GetFormatFromFIF( fif ), msg );
									}
									else
									{
										logWARNING( msg );
									}
								} );
								*/
}
