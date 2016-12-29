#include "CTexture.hpp"

#include <glm/glm.hpp>

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/renderer/GLHelper.hpp"

CTexture::CTexture( const std::shared_ptr< const CImage > &image, const GLint internalFormat ) :
	m_type { type::TEX_2D }
{
	glCreateTextures( GL_TEXTURE_2D, 1, &m_texID );

	const auto &size = image->Size();

	const GLchar maxMipLevel = floor( glm::log2( std::max( size.width, size.height ) ) ) + 1;
	glTextureParameteri( m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_texID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage2D(	m_texID,
						maxMipLevel,
						static_cast< GLenum >( internalFormat ),
						size.width,
						size.height );

	glTextureSubImage2D(	m_texID,
							0, // level
							0, // xoffset
							0, // yoffset
							size.width,
							size.height,
							GLHelper::GLFormatFromImage( image ),
							GL_UNSIGNED_BYTE,
							image->RawPixelData() );

	glGenerateTextureMipmap( m_texID );
}

CTexture::CTexture( const CCubemapData &cubemapData, const GLint internalFormat ) :
	m_type { type::TEX_CUBE_MAP }
{
	glCreateTextures( GL_TEXTURE_CUBE_MAP, 1, &m_texID );

	glTextureParameteri( m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_texID, GL_TEXTURE_MAX_LEVEL, 0 );

	const auto faces = cubemapData.getFaces();

	auto &size = faces[ 0 ]->Size();

	glTextureStorage2D(	m_texID,
						1,
						static_cast< GLenum >( internalFormat ),
						size.width,
						size.height );

	//for( std::uint8_t faceNum = 0; faceNum < CCubemapData::countCubemapFaces; faceNum++ )
	std::uint8_t faceNum = 0;
	for( const auto face : faces )
	{
		glTextureSubImage3D(	m_texID,
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
}

CTexture::CTexture( const C2DArrayData &arrayData, const GLint internalFormat ) :
	m_type { type::TEX_2D_ARRAY }
{
	glCreateTextures( GL_TEXTURE_2D_ARRAY, 1, &m_texID );

	auto const layers = arrayData.getLayers();

	const auto &size = layers[ 0 ]->Size();

	const GLchar maxMipLevel = floor( glm::log2( std::max( size.width, size.height ) ) ) + 1;
	glTextureParameteri( m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_texID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage3D(	m_texID,
						maxMipLevel,
						static_cast< GLenum >( internalFormat ),
						size.width,
						size.height,
						layers.size() );

	std::uint8_t layerNum = 0;
	for( const auto layer : layers )
	{
		glTextureSubImage3D(	m_texID,
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

	glGenerateTextureMipmap( m_texID );
}

CTexture::~CTexture( void )
{
	glDeleteTextures( 1, &m_texID );
}

void CTexture::BindToUnit( const GLuint unit ) const
{
	CGLState::BindTextureToUnit( m_texID, unit );
}

CTexture::type CTexture::Type( void ) const
{
	return( m_type );
}
