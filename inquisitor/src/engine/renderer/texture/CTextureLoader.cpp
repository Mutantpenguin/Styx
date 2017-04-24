#include "CTextureLoader.hpp"

#include <glm/glm.hpp>

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include "src/engine/renderer/GL.h"
#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/helper/image/ImageHandler.hpp"

#include "src/engine/renderer/GLHelper.hpp"

#include "src/engine/renderer/texture/CCubemapData.hpp"
#include "src/engine/renderer/texture/C2DArrayData.hpp"

CTextureLoader::CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	m_filesystem { p_filesystem },
	// clamp the value so we don't get too bad texture-quality
	m_iPicMip { std::min( p_settings.renderer.textures.picmip, MAX_TEXTURE_PICMIP ) },
	m_internalTextureFormat2D { openGlAdapter.PreferredInternalTextureFormat2D() },
	m_internalTextureFormatCube { openGlAdapter.PreferredInternalTextureFormatCube() },
	m_internalTextureFormat2DArray { openGlAdapter.PreferredInternalTextureFormat2DArray() },
	m_dummyImage { ImageHandler::GenerateCheckerImage( CSize( 64, 64 ) ) }
{
	// fetch the maximal texture size
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_iMaxTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::Meta::getString( GL_MAX_TEXTURE_SIZE ), m_iMaxTextureSize );

	// fetch the maximal cubemap texture size
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_iMaxCubeMapTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::Meta::getString( GL_MAX_CUBE_MAP_TEXTURE_SIZE ), m_iMaxCubeMapTextureSize );

	if( !m_dummyImage )
	{
		logERROR( "checker-image for the dummy-texture couldn't be generated" );
		throw std::exception();
	}
}


void CTextureLoader::FromFile( const std::string &path, std::shared_ptr< CTexture > tex ) const
{
	// TODO implement loading of compressed images in our own format

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
		FromDummy( tex );
	}
	else
	{
		const std::string fileExtension = path.substr( path.find_last_of( "." ) + 1 );

		if( fileExtension == std::string( "cub" ) )
		{
			if( !FromCubeFile( path, tex ) )
			{
				FromDummy( tex );
			}
		}
		else if( fileExtension == std::string( "arr" ) )
		{
			if( !From2DArrayFile( path, tex ) )
			{
				FromDummy( tex );
			}
		}
		else
		{
			if( !FromImageFile( path, tex ) )
			{
				FromDummy( tex );
			}
		}
	}
}

void CTextureLoader::FromImage( const std::shared_ptr< const CImage > &image, std::shared_ptr< CTexture > tex ) const
{
	tex->m_type = CTexture::type::TEX_2D;

	glCreateTextures( GL_TEXTURE_2D, 1, &tex->m_texID );

	const auto &size = image->Size();

	const GLchar maxMipLevel = floor( glm::log2( std::max( size.width, size.height ) ) ) + 1;
	glTextureParameteri( tex->m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( tex->m_texID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage2D(	tex->m_texID,
						maxMipLevel,
						static_cast< GLenum >( m_internalTextureFormat2D ),
						size.width,
						size.height );

	glTextureSubImage2D(	tex->m_texID,
							0, // level
							0, // xoffset
							0, // yoffset
							size.width,
							size.height,
							GLHelper::GLFormatFromImage( image ),
							GL_UNSIGNED_BYTE,
							image->RawPixelData() );

	glGenerateTextureMipmap( tex->m_texID );
}

bool CTextureLoader::FromImageFile( const std::string &path, std::shared_ptr< CTexture > tex ) const
{
	const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path, m_iMaxTextureSize, m_iPicMip, false );

	if( !image )
	{
		logWARNING( "image '{0}' couldn't be loaded", path );
		return( false );
	}
	else
	{
		FromImage( image, tex );
		return( true );
	}
}

bool CTextureLoader::FromCubeFile( const std::string &path, std::shared_ptr< CTexture > tex ) const
{
	json root;

	try
	{
		root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, e.what() );
		return( false );
	}

	const auto json_faces = root.find( "faces" );

	if(	json_faces == root.cend() )
	{
		logWARNING( "no faces defined in '{0}'", path );
		return( false );
	}
	else if( json_faces->size() < CCubemapData::countCubemapFaces )
	{
		logWARNING( "there are only {0} faces defined in '{1}'", json_faces->size(), path );
		return( false );
	}
	else if( json_faces->size() > CCubemapData::countCubemapFaces )
	{
		logWARNING( "there are too many ( {0} ) faces defined in '{1}'", json_faces->size(), path );
		return( false );
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
			return( false );
		}
		else
		{
			if( !cubemapData.AddFace( faceNum, image ) )
			{
				logWARNING( "failed to add face '{0}' for cubemap '{1}'", (*json_faces)[ faceNum ].get<std::string>(), path );
				return( false );
			}
		}
	}

	if( cubemapData.isComplete() )
	{
		tex->m_type = CTexture::type::TEX_CUBE_MAP;

		glCreateTextures( GL_TEXTURE_CUBE_MAP, 1, &tex->m_texID );

		glTextureParameteri( tex->m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( tex->m_texID, GL_TEXTURE_MAX_LEVEL, 0 );

		const auto &faces = cubemapData.getFaces();

		const auto &size = faces[ 0 ]->Size();

		glTextureStorage2D(	tex->m_texID,
							1,
							static_cast< GLenum >( m_internalTextureFormatCube ),
							size.width,
							size.height );

		std::uint8_t faceNum = 0;
		for( const auto &face : faces )
		{
			glTextureSubImage3D(	tex->m_texID,
									0, // level
									0, // xoffset
									0, // yoffset
									faceNum++, // zoffset
									face->Size().width,
									face->Size().height,
									1, // depth
									GLHelper::GLFormatFromImage( face ),
									GL_UNSIGNED_BYTE,
									face->RawPixelData() );
		}

		return( true );
	}
	else
	{
		logWARNING( "incomplete cubemap for '{0}'", path );
		return( false );
	}
}

bool CTextureLoader::From2DArrayFile( const std::string &path, std::shared_ptr< CTexture > tex ) const
{
	json root;

	try
	{
		root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, e.what() );
		return( false );
	}

	const auto json_layers = root.find( "layers" );

	if( json_layers == root.cend() )
	{
		logWARNING( "no layers defined in '{0}'", path );
		return( false );
	}
	else if( json_layers->size() > std::numeric_limits< std::uint8_t >::max() )
	{
		logWARNING( "more than the maximum of {0} layers defined in '{1}'", std::numeric_limits< std::uint8_t >::max(), path );
		return( false );
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
			return( false );
		}
		else
		{
			if( !arrayData.AddLayer( image ) )
			{
				logWARNING( "failed to add layer '{0}' for array texture '{1}'", layer.get<std::string>(), path );
				return( false );
			}
		}
	}

	tex->m_type = CTexture::type::TEX_2D_ARRAY;

	glCreateTextures( GL_TEXTURE_2D_ARRAY, 1, &tex->m_texID );

	auto const layers = arrayData.getLayers();

	const auto &size = layers[ 0 ]->Size();

	const GLchar maxMipLevel = floor( glm::log2( std::max( size.width, size.height ) ) ) + 1;
	glTextureParameteri( tex->m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( tex->m_texID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage3D(	tex->m_texID,
						maxMipLevel,
						static_cast< GLenum >( m_internalTextureFormat2DArray ),
						size.width,
						size.height,
						layers.size() );

	std::uint8_t layerNum = 0;
	for( const auto layer : layers )
	{
		glTextureSubImage3D(	tex->m_texID,
								0, // level
								0, // xoffset
								0, // yoffset
								layerNum++, // zoffset
								layer->Size().width,
								layer->Size().height,
								1, // depth
								GLHelper::GLFormatFromImage( layer ),
								GL_UNSIGNED_BYTE,
								layer->RawPixelData() );
	}

	glGenerateTextureMipmap( tex->m_texID );

	return( true );
}

void CTextureLoader::FromDummy( std::shared_ptr< CTexture > tex ) const
{
	tex->Reset();

	// Creates a checkerboard-like dummy-texture
	FromImage( m_dummyImage, tex );
}
