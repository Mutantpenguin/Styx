#include "CTextureManager.hpp"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	// TODO still needed? #define WINVER 0x0501
	#include <windows.h>
#endif

#include <json/json.h>

#include "CCubemapData.hpp"
#include "C2DArrayData.hpp"

#include "../../helper/image/ImageHandler.hpp"

#include "../CGLState.hpp"

#include "../../logger/CLogger.hpp"


const std::uint8_t CTextureManager::MAX_PICMIP;

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
		LOG( logWARNING ) << "there are still '" + std::to_string( m_textures.size() ) + "' existing m_textures";
		#ifdef INQ_DEBUG
		for( auto texture : m_textures )
		{
			LOG( logDEBUG ) << "  " << texture.first;
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
	LOG( logDEBUG ) << "GL_MAX_TEXTURE_SIZE is '" << m_iMaxTextureSize << "'";

	// look out for the maximal cubemap texture size
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_iMaxCubeMapTextureSize );
	LOG( logDEBUG ) << "GL_MAX_CUBE_MAP_TEXTURE_SIZE is '" << m_iMaxCubeMapTextureSize << "'";

	/* TODO try to use GL_ARB_internalformat_query2 when available on r600
	if( rendererCapabilities.isSupported( GLextension::GL_ARB_internalformat_query2 ) )
	{
		LOG( logERROR ) << "GL_ARB_internalformat_query supported";

		//GLenum format, type;
		GLint format, type;
		gl42::glGetInternalformativ( GL_TEXTURE_2D, GL_RGBA8, gl43::GL_INTERNALFORMAT_PREFERRED, 1, &format );
		//gl43::glGetInternalformativ( GL_TEXTURE_2D, GL_RGBA8, gl43::GL_TEXTURE_IMAGE_FORMAT, 1, &format );
		//gl43::glGetInternalformativ( GL_TEXTURE_2D, GL_RGBA8, gl43::GL_TEXTURE_IMAGE_TYPE, 1, &type );

		LOG( logERROR ) << "format : " << glbinding::Meta::getString( static_cast< GLenum >( format ) );
		//LOG( logERROR ) << "type : " << glbinding::Meta::getString( type );
	}
	else
	{
		LOG( logINFO ) << "using '" << glbinding::Meta::getString( m_internalTextureFormat ) << "' as internal texture format";
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
		LOG( logWARNING ) << "'" << path << "' does not exist";
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
		LOG( logWARNING ) << "failed to create texture from file '" << path << "'";
		return( m_dummyTexture );
	}
}

std::shared_ptr< CTexture > CTextureManager::GetDummyTexture( void ) const
{
	return( m_dummyTexture );
}

std::shared_ptr< CTexture > CTextureManager::Create2DTextureFromFile( const std::string &path )
{
	const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path, m_iMaxTextureSize, m_iPicMip, false );

	if( !image )
	{
		LOG( logWARNING ) << "image '" << path << "' couldn't be loaded";
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
		LOG( logWARNING ) << "failed to parse '" << path << "' because of " << reader.getFormattedErrorMessages();
		return( nullptr );
	}

	const Json::Value json_faces = root[ "faces" ];

	if(	json_faces.empty() )
	{
		LOG( logWARNING ) << "no faces defined in '" << path << "'";
		return( nullptr );
	}
	else if( json_faces.size() < CCubemapData::countCubemapFaces )
	{
		LOG( logWARNING ) << "there are only " << json_faces.size() << " faces defined in '" << path << "'";
		return( nullptr );
	}
	else if( json_faces.size() > CCubemapData::countCubemapFaces )
	{
		LOG( logWARNING ) << "there are too many ( " << json_faces.size() << " ) faces defined in '" << path << "'";
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
			LOG( logWARNING ) << "failed to load image '" << path_to_face << "' for cubemap '" << path << "'";
			return( nullptr );
		}
		else
		{
			if( !cubemapData->AddFace( faceNum, image ) )
			{
				LOG( logWARNING ) << "failed to add face '" << json_faces[ faceNum ].asString() << "' for cubemap '" << path << "'";
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
		LOG( logWARNING ) << "failed to parse '" << path << "' because of " << reader.getFormattedErrorMessages();
		return( nullptr );
	}

	const Json::Value json_layers = root[ "layers" ];

	if(	json_layers.empty() )
	{
		LOG( logWARNING ) << "no layers defined in '" << path << "'";
		return( nullptr );
	}
	else if( json_layers.size() > UINT8_MAX )
	{
		LOG( logWARNING ) << "more than the maximum of " << UINT8_MAX << " layers defined in '" << path << "'";
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
			LOG( logWARNING ) << "failed to load image '" << path_to_layer << "' for array texture '" << path << "'";
			return( nullptr );
		}
		else
		{
			if( !arrayData->AddLayer( image ) )
			{
				LOG( logWARNING ) << "failed to add layer '" << layer.asString() << "' for array texture '" << path << "'";
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
		LOG( logERROR ) << "checker-image for the dummy-texture couldn't be generated";
		return( false );
	}
	else
	{
		m_dummyTexture = std::make_shared< CTexture >( image );

		return( true );
	}
}
