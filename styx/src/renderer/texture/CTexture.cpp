#include "CTexture.hpp"

#include "src/renderer/CGLState.hpp"

CTexture::~CTexture()
{
	glDeleteTextures( 1, &m_id );
}

void CTexture::BindToUnit( const GLuint unit ) const
{
	CGLState::BindTextureToUnit( m_id, unit );
}

CTexture::EType CTexture::Type() const
{
	return( m_type );
}

void CTexture::Type( const EType type )
{
	m_type = type;
}

void CTexture::Reset()
{
	glDeleteTextures( 1, &m_id );

	m_id = 0;
}

GLuint &CTexture::OpenGLID()
{
	return( m_id );
}
