#include "CTextureLoader.hpp"

#include <cmath>

#include <glbinding-aux/Meta.h>

#include "external/json/json.hpp"
using json = nlohmann::json;

#include "src/renderer/GL.h"

#include "src/logger/CLogger.hpp"

#include "src/helper/image/ImageHandler.hpp"

#include "src/renderer/GLHelper.hpp"

#include "src/core/StyxException.hpp"

CTextureLoader::CTextureLoader( const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	m_filesystem { p_filesystem },
	m_openGlAdapter { openGlAdapter },
	m_dummyImage { ImageHandler::GenerateCheckerImage( CSize( 64, 64 ), CColor( 1.0f, 0.0f, 1.0f, 1.0f ), CColor( 0.0f, 0.0f, 0.0f, 1.0f ) ) }
{
	if( !m_dummyImage )
	{
		THROW_STYX_EXCEPTION( "checker-image for the dummy-texture couldn't be generated" )
	}

	logINFO( "texture loader was initialized" );
}

CTextureLoader::~CTextureLoader()
{
	logINFO( "texture loader is shutting down" );
}

void CTextureLoader::FromFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not contain a filename", path.generic_string() );
	}

	// TODO use libktx too?

	const std::string fileExtensionString = path.extension().generic_string();

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "texture file '{0}' does not exist", path.generic_string() );
		
		if( fileExtensionString == std::string( ".cub" ) )
		{
			FromCubeDummy( texture );
		}
		else if( fileExtensionString == std::string( ".arr" ) )
		{
			From2DArrayDummy( texture );
		}
		else
		{
			FromImageDummy( texture );
		}
	}
	else
	{
		if( fileExtensionString == std::string( ".cub" ) )
		{
			if( !FromCubeFile( texture, path ) )
			{
				FromCubeDummy( texture );
			}
		}
		else if( fileExtensionString == std::string( ".arr" ) )
		{
			if( !From2DArrayFile( texture, path ) )
			{
				From2DArrayDummy( texture );
			}
		}
		else
		{
			if( !FromImageFile( texture, path ) )
			{
				FromImageDummy( texture );
			}
		}
	}
}

bool CTextureLoader::FromImageFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const
{
	const std::shared_ptr<const CImage> image = ImageHandler::Load( m_filesystem, path, m_openGlAdapter.MaxTextureSize(), false );

	if( !image )
	{
		logWARNING( "image '{0}' couldn't be loaded", path.generic_string() );
		return( false );
	}
	else
	{
		FromImage( texture, image );
		return( true );
	}
}

bool CTextureLoader::FromCubeFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const
{
	json root;

	try
	{
		root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path.generic_string(), e.what() );
		return( false );
	}

	const auto json_faces = root.find( "faces" );

	if( json_faces == root.end() )
	{
		logWARNING( "no faces defined in '{0}'", path.generic_string() );
		return( false );
	}
	else if( json_faces->size() < CCubemapData::cubemapFaceCount )
	{
		logWARNING( "there are only {0} faces defined in '{1}'", json_faces->size(), path.generic_string() );
		return( false );
	}
	else if( json_faces->size() > CCubemapData::cubemapFaceCount )
	{
		logWARNING( "there are too many ( {0} ) faces defined in '{1}'", json_faces->size(), path.generic_string() );
		return( false );
	}

	const auto directoryOfFaces = path.parent_path();

	CCubemapData cubemapData;

	for( u8 faceNum = 0; faceNum < CCubemapData::cubemapFaceCount; ++faceNum )
	{
		const auto pathOfFace = directoryOfFaces / (*json_faces)[ faceNum ].get<std::string>();
		const std::shared_ptr<const CImage> image = ImageHandler::Load( m_filesystem, pathOfFace, m_openGlAdapter.MaxCubeMapTextureSize(), true );
		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for cubemap '{1}'", pathOfFace.generic_string(), path.generic_string() );
			return( false );
		}
		else
		{
			if( !cubemapData.SetFace( faceNum, image ) )
			{
				logWARNING( "failed to add face '{0}' for cubemap '{1}'", (*json_faces)[ faceNum ].get<std::string>(), path.generic_string() );
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
		logWARNING( "unable to load cubemap for '{0}'", path.generic_string() );
		return( false );
	}
}

bool CTextureLoader::From2DArrayFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const
{
	json root;

	try
	{
		root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path.generic_string(), e.what() );
		return( false );
	}

	const auto json_layers = root.find( "layers" );

	if( json_layers == root.end() )
	{
		logWARNING( "no layers defined in '{0}'", path.generic_string() );
		return( false );
	}
	else if( json_layers->size() > std::numeric_limits<u8>::max() )
	{
		logWARNING( "more than the maximum of {0} layers defined in '{1}'", std::numeric_limits<u8>::max(), path.generic_string() );
		return( false );
	}

	const auto directoryOfLayers = path.parent_path();

	C2DArrayData arrayData;

	for( const auto &layer : (*json_layers) )
	{
		const auto pathOfLayer = directoryOfLayers / layer.get<std::string>();

		const std::shared_ptr<const CImage> image = ImageHandler::Load( m_filesystem, pathOfLayer, m_openGlAdapter.MaxTextureSize(), false );

		if( nullptr == image )
		{
			logWARNING( "failed to load image '{0}' for array texture '{1}'", pathOfLayer.generic_string(), path.generic_string() );
			return( false );
		}
		else
		{
			if( !arrayData.AddLayer( image ) )
			{
				logWARNING( "failed to add layer '{0}' for array texture '{1}'", layer.get<std::string>(), path.generic_string() );
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
		logWARNING( "unable to load 2D array for '{0}'", path.generic_string() );
		return( false );
	}
}

void CTextureLoader::FromImage( const std::shared_ptr<CTexture> &texture, const std::shared_ptr<const CImage> &image )
{
	texture->Target = GL_TEXTURE_2D;

	glCreateTextures( texture->Target, 1, &texture->GLID );

	const auto &size = image->Size();

	const GLchar maxMipLevel = static_cast<GLchar>( floor( log2( std::max( size.width, size.height ) ) ) ) + 1;
	glTextureParameteri( texture->GLID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( texture->GLID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage2D( texture->GLID,
						maxMipLevel,
						PreferredInternalFormatFromImage( texture->Target, image ),
						size.width,
						size.height );

	glTextureSubImage2D(	texture->GLID,
							0, // level
							0, // xoffset
							0, // yoffset
							size.width,
							size.height,
							FormatFromImage( image ),
							GL_UNSIGNED_BYTE,
							image->RawPixelData() );

	glGenerateTextureMipmap( texture->GLID );
}

bool CTextureLoader::FromCubemapData( const std::shared_ptr<CTexture> &texture, const CCubemapData &cubemapData ) const
{
	if( cubemapData.isComplete() )
	{
		texture->Target = GL_TEXTURE_CUBE_MAP;

		glCreateTextures( texture->Target, 1, &texture->GLID );

		glTextureParameteri( texture->GLID, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( texture->GLID, GL_TEXTURE_MAX_LEVEL, 0 );

		const auto &faces = cubemapData.getFaces();

		const auto &size = faces[ 0 ]->Size();

		glTextureStorage2D( texture->GLID,
							1, // levels
							PreferredInternalFormatFromImage( texture->Target, faces[ 0 ] ),
							size.width,
							size.height );

		u8 faceNum = 0;
		for( const auto &face : faces )
		{
			glTextureSubImage3D(	texture->GLID,
									0, // level
									0, // xoffset
									0, // yoffset
									faceNum++, // zoffset
									face->Size().width,
									face->Size().height,
									1, // depth
									FormatFromImage( face ),
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

bool CTextureLoader::From2DArrayData( const std::shared_ptr<CTexture> &texture, const C2DArrayData &arrayData ) const
{
	const auto &layers = arrayData.getLayers();

	if( layers.size() > 0 )
	{
		texture->Target = GL_TEXTURE_2D_ARRAY;

		glCreateTextures( texture->Target, 1, &texture->GLID );

		const auto &size = layers[ 0 ]->Size();

		const GLchar maxMipLevel = static_cast<GLchar>( floor( log2( std::max( size.width, size.height ) ) ) ) + 1;
		glTextureParameteri( texture->GLID, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( texture->GLID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

		glTextureStorage3D( texture->GLID,
							maxMipLevel,
							PreferredInternalFormatFromImage( texture->Target, layers[ 0 ] ),
							size.width,
							size.height,
							layers.size() );

		u8 layerNum = 0;
		for( const auto &layer : layers )
		{
			glTextureSubImage3D(	texture->GLID,
									0, // level
									0, // xoffset
									0, // yoffset
									layerNum++, // zoffset
									layer->Size().width,
									layer->Size().height,
									1, // depth
									FormatFromImage( layer ),
									GL_UNSIGNED_BYTE,
									layer->RawPixelData() );
		}

		glGenerateTextureMipmap( texture->GLID );

		return( true );
	}
	else
	{
		logWARNING( "empty 2D array" );
		return( false );
	}
}

void CTextureLoader::FromImageDummy( const std::shared_ptr<CTexture> &texture ) const
{
	texture->Reset();

	// Creates a checkerboard-like dummy-texture
	FromImage( texture, m_dummyImage );
}

void CTextureLoader::FromCubeDummy( const std::shared_ptr<CTexture> &texture ) const
{
	texture->Reset();

	// Creates a checkerboard-like dummy-texture

	CCubemapData cubemapData;
	for( u8 faceNum = 0; faceNum < CCubemapData::cubemapFaceCount; ++faceNum )
	{
		if( !cubemapData.SetFace( faceNum, m_dummyImage ) )
		{
			throw std::runtime_error( fmt::format( "failed to add face '{0}' for dummy cubemap texture", faceNum ) );
		}
	}

	FromCubemapData( texture, cubemapData );
}

void CTextureLoader::From2DArrayDummy( const std::shared_ptr<CTexture> &texture ) const
{
	texture->Reset();

	// Creates a checkerboard-like dummy-texture with flashing

	C2DArrayData arrayData;

	if( !arrayData.AddLayer( m_dummyImage )
		||
		!arrayData.AddLayer( ImageHandler::GenerateCheckerImage( m_dummyImage->Size(), CColor( 0.0f, 1.0f, 0.0f ), CColor( 1.0f, 1.0f, 1.0f ) ) ) )
	{
		throw std::runtime_error( "failed to add layer for dummy 2D array texture" );
	}

	From2DArrayData( texture, arrayData );
}

GLenum CTextureLoader::PreferredInternalFormatFromImage( const GLenum target, const std::shared_ptr<const CImage> &image )
{
	GLenum internalFormat;
	
	switch( image->BPP() )
	{
		case 8:
			internalFormat = GL_R8;
			break;
		
		case 16:
			internalFormat = GL_RG8;
			break;
		
		case 24:
			internalFormat = GL_RGB8;
			break;
		
		case 32:
			internalFormat = GL_RGBA8;
			break;
		
		default:
			throw std::runtime_error( fmt::format( "cannot deduce GL format from image with '{0}'bpp", image->BPP() ) );
	}
	
	GLint m_preferredInternalTextureFormat;
	
	glGetInternalformativ( target, internalFormat, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormat );
	
	return( static_cast<GLenum>( m_preferredInternalTextureFormat ) );
}

GLenum CTextureLoader::FormatFromImage( const std::shared_ptr<const CImage> &image )
{
	switch( image->BPP() )
	{
		case 8:
			return( GL_RED );
			break;
		
		case 16:
			return( GL_RG );
			break;
		
		case 24:
			return( GL_BGR );
			break;
		
		case 32:
			return( GL_BGRA );
			break;
		
		default:
			throw std::runtime_error( fmt::format( "cannot deduce GL format from image with '{0}'bpp", image->BPP() ) );
	}
}
