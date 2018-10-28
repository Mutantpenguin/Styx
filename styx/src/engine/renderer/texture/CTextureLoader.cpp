#include "CTextureLoader.hpp"

#include <cmath>

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include "src/engine/renderer/GL.h"
#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/helper/Path.hpp"

#include "src/engine/helper/image/ImageHandler.hpp"

#include "src/engine/renderer/GLHelper.hpp"

CTextureLoader::CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	m_filesystem { p_filesystem },
	// clamp the value so we don't get too bad texture-quality
	m_iPicMip { std::min( p_settings.renderer.textures.picmip, MAX_TEXTURE_PICMIP ) },
	m_openGlAdapter { openGlAdapter },
	m_dummyImage { ImageHandler::GenerateCheckerImage( CSize( 64, 64 ) ) }
{
	if( !m_dummyImage )
	{
		logERROR( "checker-image for the dummy-texture couldn't be generated" );
		throw std::exception();
	}

	logINFO( "texture loader was initialized" );
}

CTextureLoader::~CTextureLoader()
{
	logINFO( "texture loader is shutting down" );
}

void CTextureLoader::FromFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const
{
	// TODO implement loading of compressed images in our own format
	// TODO or just use libktx?

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "texture file '{0}' does not exist", path );
		FromDummy( texture );
	}
	else
	{
		const std::string fileExtension = Path::Extension( path );

		if( fileExtension == std::string( "cub" ) )
		{
			if( !FromCubeFile( texture, path ) )
			{
				FromDummy( texture );
			}
		}
		else if( fileExtension == std::string( "arr" ) )
		{
			if( !From2DArrayFile( texture, path ) )
			{
				FromDummy( texture );
			}
		}
		else
		{
			if( !FromImageFile( texture, path ) )
			{
				FromDummy( texture );
			}
		}
	}
}

bool CTextureLoader::FromImageFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const
{
	const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, path, m_openGlAdapter.MaxTextureSize(), m_iPicMip, false );

	if( !image )
	{
		logWARNING( "image '{0}' couldn't be loaded", path );
		return( false );
	}
	else
	{
		FromImage( texture, image );
		return( true );
	}
}

bool CTextureLoader::FromCubeFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const
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

	if( json_faces == root.end() )
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

	const std::string directoryOfFaces = Path::Directory( path );

	CCubemapData cubemapData;

	for( u8 faceNum = 0; faceNum < CCubemapData::countCubemapFaces; ++faceNum )
	{
		const std::string pathOfFace = directoryOfFaces + (*json_faces)[ faceNum ].get<std::string>();
		const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, pathOfFace, m_openGlAdapter.MaxCubeMapTextureSize(), m_iPicMip, true );
		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for cubemap '{1}'", pathOfFace, path );
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

	if( FromCubemapData( texture, cubemapData ) )
	{
		return( true );
	}
	else
	{
		logWARNING( "unable to load cubemap for '{0}'", path );
		return( false );
	}
}

bool CTextureLoader::From2DArrayFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const
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

	if( json_layers == root.end() )
	{
		logWARNING( "no layers defined in '{0}'", path );
		return( false );
	}
	else if( json_layers->size() > std::numeric_limits< u8 >::max() )
	{
		logWARNING( "more than the maximum of {0} layers defined in '{1}'", std::numeric_limits< u8 >::max(), path );
		return( false );
	}

	const std::string directoryOfLayers = Path::Directory( path );

	C2DArrayData arrayData;

	for( const auto &layer : (*json_layers) )
	{
		const std::string pathOfLayer = directoryOfLayers + layer.get<std::string>();
		const std::shared_ptr< const CImage > image = ImageHandler::Load( m_filesystem, pathOfLayer, m_openGlAdapter.MaxTextureSize(), m_iPicMip, false );

		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for array texture '{1}'", pathOfLayer, path );
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

	if( From2DArrayData( texture, arrayData ) )
	{
		return( true );
	}
	else
	{
		logWARNING( "unable to load 2D array for '{0}'", path );
		return( false );
	}
}

void CTextureLoader::FromImage( const std::shared_ptr< CTexture > &texture, const std::shared_ptr< const CImage > &image ) const
{
	texture->Type( CTexture::TextureType::TEX_2D );

	auto &id = texture->OpenGLID();

	glCreateTextures( GL_TEXTURE_2D, 1, &id );

	const auto &size = image->Size();

	const GLchar maxMipLevel = floor( log2( std::max( size.width, size.height ) ) ) + 1;
	glTextureParameteri( id, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( id, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage2D(	id,
						maxMipLevel,
						static_cast< GLenum >( m_openGlAdapter.PreferredInternalTextureFormat2D() ),
						size.width,
						size.height );

	glTextureSubImage2D(	id,
							0, // level
							0, // xoffset
							0, // yoffset
							size.width,
							size.height,
							GLHelper::GLFormatFromImage( image ),
							GL_UNSIGNED_BYTE,
							image->RawPixelData() );

	glGenerateTextureMipmap( id );
}

bool CTextureLoader::FromCubemapData( const std::shared_ptr< CTexture > &texture, const CCubemapData &cubemapData ) const
{
	if( cubemapData.isComplete() )
	{
		texture->Type( CTexture::TextureType::TEX_CUBE_MAP );

		auto &id = texture->OpenGLID();

		glCreateTextures( GL_TEXTURE_CUBE_MAP, 1, &id );

		glTextureParameteri( id, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( id, GL_TEXTURE_MAX_LEVEL, 0 );

		const auto &faces = cubemapData.getFaces();

		const auto &size = faces[ 0 ]->Size();

		glTextureStorage2D(	id,
							1, // levels
							static_cast< GLenum >( m_openGlAdapter.PreferredInternalTextureFormatCube() ),
							size.width,
							size.height );

		u8 faceNum = 0;
		for( const auto &face : faces )
		{
			glTextureSubImage3D(	id,
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
		logWARNING( "incomplete cubemap" );
		return( false );
	}
}

bool CTextureLoader::From2DArrayData( const std::shared_ptr< CTexture > &texture, const C2DArrayData &arrayData ) const
{
	const auto &layers = arrayData.getLayers();

	if( layers.size() > 0 )
	{
		texture->Type( CTexture::TextureType::TEX_2D_ARRAY );

		auto &id = texture->OpenGLID();

		glCreateTextures( GL_TEXTURE_2D_ARRAY, 1, &id );

		const auto &size = layers[ 0 ]->Size();

		const GLchar maxMipLevel = floor( log2( std::max( size.width, size.height ) ) ) + 1;
		glTextureParameteri( id, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( id, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

		glTextureStorage3D(	id,
							maxMipLevel,
							static_cast< GLenum >( m_openGlAdapter.PreferredInternalTextureFormat2DArray() ),
							size.width,
							size.height,
							layers.size() );

		u8 layerNum = 0;
		for( const auto &layer : layers )
		{
			glTextureSubImage3D(	id,
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

		glGenerateTextureMipmap( id );

		return( true );
	}
	else
	{
		logWARNING( "empty 2D array" );
		return( false );
	}
}

void CTextureLoader::FromDummy( const std::shared_ptr< CTexture > &texture ) const
{
	texture->Reset();

	// Creates a checkerboard-like dummy-texture
	FromImage( texture, m_dummyImage );
}
