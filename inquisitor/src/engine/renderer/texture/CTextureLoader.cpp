#include "CTextureLoader.hpp"

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/helper/image/ImageHandler.hpp"

CTextureLoader::CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	m_filesystem { p_filesystem },
	// clamp the value so we don't get too bad texture-quality
	m_iPicMip { std::min( p_settings.renderer.textures.picmip, MAX_TEXTURE_PICMIP ) },
	m_internalTextureFormat2D { openGlAdapter.PreferredInternalTextureFormat2D() },
	m_internalTextureFormatCube { openGlAdapter.PreferredInternalTextureFormatCube() },
	m_internalTextureFormat2DArray { openGlAdapter.PreferredInternalTextureFormat2DArray() }
{
	// fetch the maximal texture size
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_iMaxTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::Meta::getString( GL_MAX_TEXTURE_SIZE ), m_iMaxTextureSize );

	// fetch the maximal cubemap texture size
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_iMaxCubeMapTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::Meta::getString( GL_MAX_CUBE_MAP_TEXTURE_SIZE ), m_iMaxCubeMapTextureSize );
}


std::shared_ptr< CTexture > CTextureLoader::FromFile( const std::string &path ) const
{
	// TODO implement loading of compressed images in our own format

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
		return( nullptr );
	}
	else
	{
		const std::string fileExtension = path.substr( path.find_last_of( "." ) + 1 );

		if( fileExtension == std::string( "cub" ) )
		{
			return( FromCubeFile( path ) );
		}
		else if( fileExtension == std::string( "arr" ) )
		{
			return( From2DArrayFile( path ) );
		}
		else
		{
			return( FromImageFile( path ) );
		}
	}
}

std::shared_ptr< CTexture > CTextureLoader::FromImage( const std::shared_ptr< const CImage > &image ) const
{
	return( std::make_shared< CTexture >( image, m_internalTextureFormat2D ) );
}

std::shared_ptr< CTexture > CTextureLoader::FromImageFile( const std::string &path ) const
{
	const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path, m_iMaxTextureSize, m_iPicMip, false );

	if( !image )
	{
		logWARNING( "image '{0}' couldn't be loaded", path );
		return( nullptr );
	}
	else
	{
		return( FromImage( image ) );
	}
}

std::shared_ptr< CTexture > CTextureLoader::FromCubeFile( const std::string &path ) const
{
	json root;

	try
	{
		root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, e.what() );
		return( nullptr );
	}

	const auto json_faces = root.find( "faces" );

	if(	json_faces == root.cend() )
	{
		logWARNING( "no faces defined in '{0}'", path );
		return( nullptr );
	}
	else if( json_faces->size() < CCubemapData::countCubemapFaces )
	{
		logWARNING( "there are only {0} faces defined in '{1}'", json_faces->size(), path );
		return( nullptr );
	}
	else if( json_faces->size() > CCubemapData::countCubemapFaces )
	{
		logWARNING( "there are too many ( {0} ) faces defined in '{1}'", json_faces->size(), path );
		return( nullptr );
	}

	const std::string path_to_faces = path.substr( 0, path.find_last_of( CFileSystem::GetDirSeparator() ) + 1 );

	CCubemapData cubemapData;

	for( std::uint8_t faceNum = 0; faceNum < CCubemapData::countCubemapFaces; ++faceNum )
	{
		const std::string path_to_face = path_to_faces + (*json_faces)[ faceNum ].get<std::string>();
		const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path_to_face, m_iMaxCubeMapTextureSize, m_iPicMip, true );
		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for cubemap '{1}'", path_to_face, path );
			return( nullptr );
		}
		else
		{
			if( !cubemapData.AddFace( faceNum, image ) )
			{
				logWARNING( "failed to add face '{0}' for cubemap '{1}'", (*json_faces)[ faceNum ].get<std::string>(), path );
				return( nullptr );
			}
		}
	}

	if( cubemapData.isComplete() )
	{
		return( std::make_shared< CTexture >( cubemapData, m_internalTextureFormatCube ) );
	}
	else
	{
		logWARNING( "incomplete cubemap for '{0}'", path );
		return( nullptr );
	}
}

std::shared_ptr< CTexture > CTextureLoader::From2DArrayFile( const std::string &path ) const
{
	json root;

	try
	{
		root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, e.what() );
		return( nullptr );
	}

	const auto json_layers = root.find( "layers" );

	if( json_layers == root.cend() )
	{
		logWARNING( "no layers defined in '{0}'", path );
		return( nullptr );
	}
	else if( json_layers->size() > UINT8_MAX )
	{
		logWARNING( "more than the maximum of {0} layers defined in '{1}'", UINT8_MAX, path );
		return( nullptr );
	}

	const std::string path_to_layers = path.substr( 0, path.find_last_of( CFileSystem::GetDirSeparator() ) + 1 );

	C2DArrayData arrayData;

	for( const auto &layer : (*json_layers) )
	{
		const std::string path_to_layer = path_to_layers + layer.get<std::string>();
		const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path_to_layer, m_iMaxTextureSize, m_iPicMip, false );

		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for array texture '{1}'", path_to_layer, path );
			return( nullptr );
		}
		else
		{
			if( !arrayData.AddLayer( image ) )
			{
				logWARNING( "failed to add layer '{0}' for array texture '{1}'", layer.get<std::string>(), path );
				return( nullptr );
			}
		}
	}

	return( std::make_shared< CTexture >( arrayData, m_internalTextureFormat2DArray ) );
}

std::shared_ptr< CTexture > CTextureLoader::FromDummy( void ) const
{
	// Creates a checkerboard-like dummy-texture

	// TODO only do this once
	const std::shared_ptr< const CImage > image = ImageHandler::GenerateCheckerImage( CSize( 64, 64 ) );

	if( !image )
	{
		logERROR( "checker-image for the dummy-texture couldn't be generated" );
		return( nullptr );
	}
	else
	{
		return( std::make_shared< CTexture >( image, m_internalTextureFormat2D ) );
	}
}
