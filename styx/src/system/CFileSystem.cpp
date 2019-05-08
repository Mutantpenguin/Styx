#include "CFileSystem.hpp"

#include "external/physfs/physfs.h"

#include "src/core/Types.hpp"

#include "src/logger/CLogger.hpp"
#include "src/logger/CLogTargetFile.hpp"

#include "src/core/StyxException.hpp"

CFileSystem::CFileSystem( const char *argv0, const std::string &organisation, const std::string &gamename, const fs::path &gameDirectory, const std::vector<std::string> &assets )
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

	const fs::path logDir( "log" );
	if( !PHYSFS_exists( logDir.generic_string().c_str() ) )
	{
		if( !PHYSFS_mkdir( logDir.generic_string().c_str() ) )
		{
			THROW_STYX_EXCEPTION( "couldn't create log-directory '{0}' because of: {1}", logDir.generic_string(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
		}
	}

	// pass an absolut path since CLogTargetFile doesn't use Physfs to write the log
	CLogger::CreateTarget<CLogTargetFile>( fs::path( PHYSFS_getWriteDir() ) / logDir );

	// put write-dir first in search path
	if( !PHYSFS_mount( PHYSFS_getWriteDir(), nullptr, 0 ) )
	{
		THROW_STYX_EXCEPTION( "adding '{0}' to search path failed because of: {1}", PHYSFS_getWriteDir(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

	// put asset-paths next in search path
	for( const std::string &asset : assets )
	{
		const fs::path asset_path = gameDirectory / asset;

		logINFO( "adding asset-path '{0}'", asset_path.generic_string() );

		if( !PHYSFS_mount( asset_path.generic_string().c_str(), nullptr, 1 ) )
		{
			THROW_STYX_EXCEPTION( "adding asset-path '{0}' to search path failed because of: {1}", asset_path.generic_string(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
		}
	}

	// put base dir last in search path
	if( !PHYSFS_mount( PHYSFS_getBaseDir(), nullptr, 1 ) )
	{
		THROW_STYX_EXCEPTION( "adding '{0}' to search path failed because of: {1}", PHYSFS_getBaseDir(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) )
	}

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

bool CFileSystem::Exists( const fs::path &path ) const
{
	return( PHYSFS_exists( path.generic_string().c_str() ) );
}

bool CFileSystem::IsDirectory( const fs::path &path ) const
{
	if( path.has_filename() )
	{
		logWARNING( "path '{0}' contains a filename", path.generic_string() );
		return( false );
	}

	PHYSFS_Stat stat;
	PHYSFS_stat( path.generic_string().c_str(), &stat );

	return( stat.filetype == PHYSFS_FILETYPE_DIRECTORY );
}

i64 CFileSystem::GetLastModTime( const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not contain a filename", path.generic_string() );
		return( false );
	}

	PHYSFS_Stat stat;
	PHYSFS_stat( path.generic_string().c_str(), &stat );

	return( stat.modtime );
}

bool CFileSystem::MakeDir( const fs::path &path ) const
{
	return( PHYSFS_mkdir( path.generic_string().c_str() ) );
}

const char* CFileSystem::GetLastError() const
{
	return( PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
}

CFileSystem::FileBuffer CFileSystem::LoadFileToBuffer( const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' contains no filename", path.generic_string() );
		return {};
	}

	PHYSFS_file* f = PHYSFS_openRead( path.generic_string().c_str() );
	if( nullptr == f )
	{
		logWARNING( "file '{0}' couldn't be opened", path.generic_string() );
		return {};
	}

	const auto length = PHYSFS_fileLength( f );

	FileBuffer buffer( static_cast<size_t>( length ) );

	const auto lengthRead = PHYSFS_readBytes( f, &buffer[ 0 ], length );

	if( lengthRead != length )
	{
		logERROR( "couldn't read all of file '{0}' because of: {1}", path.generic_string(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
		return {};
	}

	PHYSFS_close( f );

	return( buffer );
}

bool CFileSystem::SaveBufferToFile( const FileBuffer &buffer, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' contains no filename", path.generic_string() );
		return( false );
	}

	PHYSFS_file* f = PHYSFS_openWrite( path.generic_string().c_str() );

	if( nullptr == f )
	{
		logERROR( "File '{0}' couldn't be opened for writing because of: {1}", path.generic_string(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
		return( false );
	}

	const u64 lengthWrite = PHYSFS_writeBytes( f, &buffer[ 0 ], buffer.size() );

	PHYSFS_close( f );

	if( lengthWrite != buffer.size() )
	{
		logERROR( "couldn't write all of file '{0}' because of: {1}", path.generic_string(), PHYSFS_getErrorByCode( PHYSFS_getLastErrorCode() ) );
		return( false );
	}

	return( true );
}

std::string CFileSystem::LoadFileToString( const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' contains no filename", path.generic_string() );
		return {};
	}

	auto const buffer = LoadFileToBuffer( path );

	return( std::string( reinterpret_cast<const char*>( buffer.data() ), buffer.size() ) );
}
