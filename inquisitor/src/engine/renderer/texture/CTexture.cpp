#include "CTexture.hpp"

#include <glm/glm.hpp>

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/renderer/GLHelper.hpp"

CTexture::CTexture( const std::shared_ptr< const CImage > &image ) :
	m_type { type::TEX_2D }
{
	glCreateTextures( GL_TEXTURE_2D, 1, &m_texID );

	const GLchar maxMipLevel = floor( glm::log2( std::max( image->Size().width, image->Size().height ) ) ) + 1;
	glTextureParameteri( m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_texID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage2D(	m_texID,
						maxMipLevel,
						GL_RGBA8,
						image->Size().width,
						image->Size().height );

	glTextureSubImage2D(	m_texID,
							0, // level
							0, // xoffset
							0, // yoffset
							image->Size().width,
							image->Size().height,
							GLHelper::GLFormatFromImage( image ),
							GL_UNSIGNED_BYTE,
							image->RawPixelData() );

	glGenerateTextureMipmap( m_texID );
}

CTexture::CTexture( const std::unique_ptr< const CCubemapData > cubemapData ) :
	m_type { type::TEX_CUBE_MAP }
{
	glCreateTextures( GL_TEXTURE_CUBE_MAP, 1, &m_texID );

	glTextureParameteri( m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_texID, GL_TEXTURE_MAX_LEVEL, 0 );

	auto faces = cubemapData->getFaces();

	const std::shared_ptr< const CImage > &firstImage = faces[ 0 ];

	glTextureStorage2D(	m_texID,
						1,
						GL_RGBA8,
						firstImage->Size().width,
						firstImage->Size().height );

	for( std::uint8_t faceNum = 0; faceNum < CCubemapData::countCubemapFaces; faceNum++ )
	{
		const std::shared_ptr< const CImage > &image = faces[ faceNum ];

		glTextureSubImage3D(	m_texID,
								0, // level
								0, // xoffset
								0, // yoffset
								faceNum, // zoffset
								image->Size().width,
								image->Size().height,
								1, // depth
								GLHelper::GLFormatFromImage( image ),
								GL_UNSIGNED_BYTE,
								image->RawPixelData() );
	}
}

CTexture::CTexture( const std::unique_ptr< const C2DArrayData > arrayData ) :
	m_type { type::TEX_2D_ARRAY }
{
	glCreateTextures( GL_TEXTURE_2D_ARRAY, 1, &m_texID );

	auto layers = arrayData->getLayers();

	const std::shared_ptr< const CImage > &firstImage = layers[ 0 ];

	const GLchar maxMipLevel = floor( glm::log2( std::max( firstImage->Size().width, firstImage->Size().height ) ) ) + 1;
	glTextureParameteri( m_texID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_texID, GL_TEXTURE_MAX_LEVEL, maxMipLevel );

	glTextureStorage3D(	m_texID,
						maxMipLevel,
						GL_RGBA8,
						firstImage->Size().width,
						firstImage->Size().height,
						layers.size() );

	for( std::uint8_t i = 0; i < layers.size(); i++ )
	{
		const std::shared_ptr< const CImage > &image = layers[ i ];

		glTextureSubImage3D(	m_texID,
								0, // level
								0, // xoffset
								0, // yoffset
								i, // zoffset
								image->Size().width,
								image->Size().height,
								1, // depth
								GLHelper::GLFormatFromImage( image ),
								GL_UNSIGNED_BYTE,
								image->RawPixelData() );
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
