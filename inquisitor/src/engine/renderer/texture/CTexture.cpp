#include "CTexture.hpp"

#include "src/engine/renderer/CGLState.hpp"

CTexture::CTexture( void )
{
}

CTexture::~CTexture( void )
{
	glDeleteTextures( 1, &m_id );
}

void CTexture::BindToUnit( const GLuint unit ) const
{
	CGLState::BindTextureToUnit( m_id, unit );
}

CTexture::TextureType CTexture::Type( void ) const
{
	return( m_type );
}

void CTexture::Type( const TextureType type )
{
	m_type = type;
}

void CTexture::Reset( void )
{
	glDeleteTextures( 1, &m_id );

	m_id = 0;
}

GLuint &CTexture::OpenGLID( void )
{
	return( m_id );
}
