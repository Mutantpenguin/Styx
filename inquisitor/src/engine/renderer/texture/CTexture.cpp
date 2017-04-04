#include "CTexture.hpp"

#include "src/engine/renderer/CGLState.hpp"

CTexture::CTexture( void )
{
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

void CTexture::Reset( void )
{
	glDeleteTextures( 1, &m_texID );

	m_texID = 0;
}
