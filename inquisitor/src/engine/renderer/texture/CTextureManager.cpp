#include "CTextureManager.hpp"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	// TODO still needed? #define WINVER 0x0501
	#include <windows.h>
#endif

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"


CTextureManager::CTextureManager( const CSettings &p_settings, const CFileSystem &p_filesystem, const CRendererCapabilities &rendererCapabilities ) :
	m_filesystem( p_filesystem ),
	m_textureLoader( p_settings, rendererCapabilities ),
	m_dummyTexture { m_textureLoader.CreateDummyTexture() }
{
	if( nullptr == m_dummyTexture )
	{
		logERROR( "dummy-texture couldn't be generated" );
		throw Exception();
	}
}

CTextureManager::~CTextureManager( void )
{
	if( m_textures.size() > 0 )
	{
		logWARNING( "there are still '{0}' existing m_textures", m_textures.size() );
		#ifdef INQ_DEBUG
		for( auto texture : m_textures )
		{
			logDEBUG( "\t{0}", texture.first );
		}
		#endif
	}
}

void CTextureManager::Update( void )
{
	for( auto it = m_textures.cbegin(); it != m_textures.cend(); )
	{
		if( (*it).second.unique() )
		{
			m_textures.erase( it++ );
		}
		else
		{
			++it;
		}
	}
}

/**	Returns a handle to a texture.
	Looks if the texture with the specified parameters has already been loaded and returns it.
	If thats not the case it gets loaded.
	If that fails the dummy-texture gets returned.
*/
std::shared_ptr< CTexture > CTextureManager::LoadTexture( const std::string &path )
{
	// search if we already loaded the texture
	auto it = m_textures.find( path );
	if( m_textures.end() != it )
	{
		return( it->second );
	}

	// TODO implement loading of compressed images in our own format
	std::shared_ptr< CTexture > ttemp = nullptr;

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
	}
	else
	{
		if( path.substr( path.length() - 4, 4 ) == std::string( ".cub" ) )
		{
			ttemp = m_textureLoader.CreateCubeTextureFromFile( m_filesystem, path );
		}
		else if( path.substr( path.length() - 4, 4 ) == std::string( ".arr" ) )
		{
			ttemp = m_textureLoader.Create2DArrayTextureFromFile( m_filesystem, path );
		}
		else
		{
			ttemp = m_textureLoader.Create2DTextureFromFile( m_filesystem, path );
		}
	}

	if( ttemp )
	{
		m_textures[ path ] = ttemp;
		return( ttemp );
	}
	else
	{
		logWARNING( "failed to create texture from file '{0}'", path );
		return( m_dummyTexture );
	}
}
