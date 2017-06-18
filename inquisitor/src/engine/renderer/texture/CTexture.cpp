#include "CTexture.hpp"

#include "src/engine/renderer/CGLState.hpp"

CTexture::CTexture( void )
{
}

CTexture::~CTexture( void )
{
	glDeleteTextures( 1, &m_textureID );
}

void CTexture::BindToUnit( const GLuint unit ) const
{
	CGLState::BindTextureToUnit( m_textureID, unit );
}

CTexture::type CTexture::Type( void ) const
{
	return( m_type );
}

void CTexture::Reset( void )
{
	glDeleteTextures( 1, &m_textureID );

	m_textureID = 0;
}
