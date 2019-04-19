#include "CFileSystem.hpp"

#include "external/physfs/physfs.h"

#include "src/helper/Types.hpp"

#include "src/logger/CLogger.hpp"
#include "src/logger/CLogTargetFile.hpp"

#include "src/core/StyxException.hpp"

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
		THROW_STYX_EXCEPTION( "PhysicsFS version '{0}.{1}.{2}' was expected", PHYSFS_VER_MAJOR, PHYSFS_VER_MINOR, PHYSFS_VER_PATCH )
	}

	if( !PHYSFS_init( argv0 ) )
	{
		THROW_STYX_EXCEPTION( "initializing PhysicsFS failed because of: {0}", PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

	// forbid symbolic links
	PHYSFS_permitSymbolicLinks( 0 );

	std::string prefsDir = PHYSFS_getPrefDir( organisation.c_str(), gamename.c_str() );
	if( prefsDir.empty() )
	{
		THROW_STYX_EXCEPTION( "not possible to get prefs-directory because of: {0}", PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

	logDEBUG( "prefs-directory is: {0}", prefsDir );

	if( !PHYSFS_setWriteDir( prefsDir.c_str() ) )
	{
		THROW_STYX_EXCEPTION( "couldn't set write-dir to '{0}' because of: {1}", prefsDir, PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

	const std::string logDir( "log" );
	if( !PHYSFS_exists( logDir.c_str() ) )
	{
		if( !PHYSFS_mkdir( logDir.c_str() ) )
		{
			THROW_STYX_EXCEPTION( "couldn't create log-directory '{0}' because of: {1}", logDir, PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
		}
	}

	// pass an absolut path since CLogTargetFile doesn't use Physfs to write the log
	CLogger::CreateTarget< CLogTargetFile >( std::string( PHYSFS_getWriteDir() ) + logDir + std::string( PHYSFS_getDirSeparator() ) );

	// put write-dir first in search path
	if( !PHYSFS_mount( PHYSFS_getWriteDir(), nullptr, 0 ) )
	{
		THROW_STYX_EXCEPTION( "adding '{0}' to search path failed because of: {1}", PHYSFS_getWriteDir(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

	// put asset-paths next in search path
	for( const std::string &asset : assets )
	{
		const std::string asset_path = gamedir + std::string( PHYSFS_getDirSeparator() ) + asset;

		logDEBUG( "adding asset-path '{0}'", asset_path );

		if( !PHYSFS_mount( asset_path.c_str(), nullptr, 1 ) )
		{
			THROW_STYX_EXCEPTION( "adding asset-path '{0}' to search path failed because of: {1}", asset_path, PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
		}
	}

	// put base dir last in search path
	if( !PHYSFS_mount( PHYSFS_getBaseDir(), nullptr, 1 ) )
	{
		THROW_STYX_EXCEPTION( "adding '{0}' to search path failed because of: {1}", PHYSFS_getBaseDir(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

	InitialiseFreeImageIO();

	logINFO( "file system was initialized" );
}

CFileSystem::~CFileSystem()
{
	logINFO( "file system is shutting down" );

	if( !PHYSFS_deinit() )
	{
		logWARNING( "deinitializing PhysicsFS failed because of: {0}", PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
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

i64 CFileSystem::GetLastModTime( const std::string &filename ) const
{
	PHYSFS_Stat stat;
	PHYSFS_stat( filename.c_str(), &stat );

	return( stat.modtime );
}

std::string CFileSystem::GetWriteDir() const
{
	return( std::string( PHYSFS_getWriteDir() ) );
}

bool CFileSystem::MakeDir( const std::string &dirname ) const
{
	return( PHYSFS_mkdir( dirname.c_str() ) );
}

const char* CFileSystem::GetLastError() const
{
	return( PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
}

CFileSystem::FileBuffer CFileSystem::LoadFileToBuffer( const std::string &filename ) const
{
	PHYSFS_file* f = PHYSFS_openRead( filename.c_str() );
	if( nullptr == f )
	{
		logWARNING( "file '{0}' couldn't be opened", filename );
		return {};
	}

	const auto length = PHYSFS_fileLength( f );

	FileBuffer buffer( static_cast<size_t>( length ) );

	const auto lengthRead = PHYSFS_readBytes( f, &buffer[ 0 ], length );

	if( lengthRead != length )
	{
		logERROR( "couldn't read all of file '{0}' because of: {1}", filename, PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
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
		logERROR( "File '{0}' couldn't be opened for writing because of: {1}", filename, PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
		return( false );
	}

	const u64 lengthWrite = PHYSFS_writeBytes( f, &buffer[ 0 ], buffer.size() );

	PHYSFS_close( f );

	if( lengthWrite != buffer.size() )
	{
		logERROR( "couldn't write all of file '{0}' because of: {1}", filename, PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
		return( false );
	}

	return( true );
}

std::string CFileSystem::LoadFileToString( const std::string &filename ) const
{
	auto const buffer = LoadFileToBuffer( filename );

	return( std::string( reinterpret_cast<const char*>( buffer.data() ), buffer.size() ) );
}

void CFileSystem::InitialiseFreeImageIO()
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
