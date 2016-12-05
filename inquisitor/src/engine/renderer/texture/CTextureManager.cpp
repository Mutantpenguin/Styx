#include "CTextureManager.hpp"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	// TODO still needed? #define WINVER 0x0501
	#include <windows.h>
#endif

#include <glbinding/Meta.h>

#include <json/json.h>

#include "CCubemapData.hpp"
#include "C2DArrayData.hpp"

#include "../../helper/image/ImageHandler.hpp"

#include "../CGLState.hpp"

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
			logDEBUG( "  {0}", texture.first );
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

	/* TODO try to use GL_ARB_internalformat_query2 when available on r600
	if( rendererCapabilities.isSupported( GLextension::GL_ARB_internalformat_query2 ) )
	{
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

	if( !CreateDummyTexture() )
	{
		return( false );
	}

	return( true );
}

void CTextureManager::Update( void )
{
	for( auto it = m_textures.cbegin(); it != m_textures.cend(); )
	{
		auto texture = (*it).second.lock();

		if( !texture )
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
		return( it->second.lock() );
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
			ttemp = CreateCubeTextureFromFile( path );
		}
		else if( path.substr( path.length() - 4, 4 ) == std::string( ".arr" ) )
		{
			ttemp = Create2DArrayTextureFromFile( path );
		}
		else
		{
			ttemp = Create2DTextureFromFile( path );
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

std::shared_ptr< CTexture > CTextureManager::Create2DTextureFromFile( const std::string &path )
{
	const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path, m_iMaxTextureSize, m_iPicMip, false );

	if( !image )
	{
		logWARNING( "image '{0}' couldn't be loaded", path );
		return( nullptr );
	}
	else
	{
		return( std::make_shared< CTexture >( image ) );
	}
}

// TODO maybe seperate this out into its own class like the MaterialLoader?
std::shared_ptr< CTexture > CTextureManager::CreateCubeTextureFromFile( const std::string &path )
{
	Json::Value		root;
	Json::Reader	reader;
	if ( !reader.parse( m_filesystem.LoadTextFileToBuffer( path ), root ) )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, reader.getFormattedErrorMessages() );
		return( nullptr );
	}

	const Json::Value json_faces = root[ "faces" ];

	if(	json_faces.empty() )
	{
		logWARNING( "no faces defined in '{0}'", path );
		return( nullptr );
	}
	else if( json_faces.size() < CCubemapData::countCubemapFaces )
	{
		logWARNING( "there are only {0} faces defined in '{1}'", json_faces.size(), path );
		return( nullptr );
	}
	else if( json_faces.size() > CCubemapData::countCubemapFaces )
	{
		logWARNING( "there are too many ( {0} ) faces defined in '{1}'", json_faces.size(), path );
		return( nullptr );
	}

	const std::string path_to_faces = path.substr( 0, path.find_last_of( CFileSystem::GetDirSeparator() ) + 1 );

	std::unique_ptr< CCubemapData > cubemapData = std::make_unique< CCubemapData >();

	for( std::uint8_t faceNum = 0; faceNum < CCubemapData::countCubemapFaces; ++faceNum )
	{
		const std::string path_to_face = path_to_faces + json_faces[ faceNum ].asString();
		const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path_to_face, m_iMaxCubeMapTextureSize, m_iPicMip, true );
		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for cubemap '{1}'", path_to_face, path );
			return( nullptr );
		}
		else
		{
			if( !cubemapData->AddFace( faceNum, image ) )
			{
				logWARNING( "failed to add face '{0}' for cubemap '{1}'", json_faces[ faceNum ].asString(), path );
				return( nullptr );
			}
		}
	}

	if( cubemapData->isComplete() )
	{
		return( std::make_shared< CTexture >( std::move( cubemapData ) ) );
	}
	else
	{
		return( nullptr );
	}
}

std::shared_ptr< CTexture > CTextureManager::Create2DArrayTextureFromFile( const std::string &path )
{
	Json::Value		root;
	Json::Reader	reader;
	if ( !reader.parse( m_filesystem.LoadTextFileToBuffer( path ), root ) )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, reader.getFormattedErrorMessages() );
		return( nullptr );
	}

	const Json::Value json_layers = root[ "layers" ];

	if(	json_layers.empty() )
	{
		logWARNING( "no layers defined in '{0}'", path );
		return( nullptr );
	}
	else if( json_layers.size() > UINT8_MAX )
	{
		logWARNING( "more than the maximum of {0} layers defined in '{1}'", UINT8_MAX, path );
		return( nullptr );
	}

	const std::string path_to_layers = path.substr( 0, path.find_last_of( CFileSystem::GetDirSeparator() ) + 1 );

	std::unique_ptr< C2DArrayData > arrayData = std::make_unique< C2DArrayData >();

	for( const Json::Value &layer : json_layers )
	{
		const std::string path_to_layer = path_to_layers + layer.asString();
		const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path_to_layer, m_iMaxTextureSize, m_iPicMip, false );

		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for array texture '{1}'", path_to_layer, path );
			return( nullptr );
		}
		else
		{
			if( !arrayData->AddLayer( image ) )
			{
				logWARNING( "failed to add layer '{0}' for array texture '{1}'", layer.asString(), path );
				return( nullptr );
			}
		}
	}

	return( std::make_shared< CTexture >( std::move( arrayData ) ) );
}

/**	Creates a checkerboard-like dummy-texture. */
bool CTextureManager::CreateDummyTexture( void )
{
	const std::shared_ptr< const CImage > image = ImageHandler::GenerateCheckerImage( CSize( 64, 64 ) );

	if( !image )
	{
		logERROR( "checker-image for the dummy-texture couldn't be generated" );
		return( false );
	}
	else
	{
		m_dummyTexture = std::make_shared< CTexture >( image );

		return( true );
	}
}
