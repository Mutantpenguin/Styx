#include "CTextureManager.hpp"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	// TODO still needed? #define WINVER 0x0501
	#include <windows.h>
#endif

#include <glbinding/Meta.h>

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"


CTextureManager::CTextureManager( const CSettings &p_settings, const CFileSystem &p_filesystem ) :
	m_filesystem( p_filesystem ),
	// clamp the value so we don't get too bad texture-quality
	m_iPicMip( std::min( p_settings.renderer.textures.picmip, MAX_PICMIP ) )
{
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

/**	initialisation of the texture-manager
	queries the graphics-adapter to set the following flags :
	- texture filter
	- max texture size
	- texture quality
	- anisotropic filtering
	- edge-clamp
*/
bool CTextureManager::Init( const CRendererCapabilities &rendererCapabilities )
{
	// look out for the maximal texture size
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_iMaxTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::Meta::getString( GL_MAX_TEXTURE_SIZE ), m_iMaxTextureSize );

	// look out for the maximal cubemap texture size
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_iMaxCubeMapTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::Meta::getString( GL_MAX_CUBE_MAP_TEXTURE_SIZE ), m_iMaxCubeMapTextureSize );

	if( rendererCapabilities.isSupported( GLextension::GL_ARB_internalformat_query2 ) )
	{
		/* TODO try to use GL_ARB_internalformat_query2 when available on r600
		//GLenum format, type;
		GLint format, type;
		gl42::glGetInternalformativ( GL_TEXTURE_2D, GL_RGBA8, gl43::GL_INTERNALFORMAT_PREFERRED, 1, &format );
		//gl43::glGetInternalformativ( GL_TEXTURE_2D, GL_RGBA8, gl43::GL_TEXTURE_IMAGE_FORMAT, 1, &format );
		//gl43::glGetInternalformativ( GL_TEXTURE_2D, GL_RGBA8, gl43::GL_TEXTURE_IMAGE_TYPE, 1, &type );

		logERROR( "format: {0}", glbinding::Meta::getString( static_cast< GLenum >( format ) ) );
		//logERROR( "type: {0}", glbinding::Meta::getString( type ) );
	}
	else
	{
		logINFO( "using '{0}' as internal texture format", glbinding::Meta::getString( m_internalTextureFormat ) );
	}
	*/
	}


	m_dummyTexture = m_textureLoader.CreateDummyTexture();

	if( nullptr == m_dummyTexture )
	{
		return( false );
	}

	return( true );
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
			ttemp = m_textureLoader.CreateCubeTextureFromFile( m_filesystem, path, m_iMaxCubeMapTextureSize, m_iPicMip );
		}
		else if( path.substr( path.length() - 4, 4 ) == std::string( ".arr" ) )
		{
			ttemp = m_textureLoader.Create2DArrayTextureFromFile( m_filesystem, path, m_iMaxTextureSize, m_iPicMip );
		}
		else
		{
			ttemp = m_textureLoader.Create2DTextureFromFile( m_filesystem, path, m_iMaxTextureSize, m_iPicMip );
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
