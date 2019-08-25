#include "CTexture.hpp"

#include "src/renderer/CGLState.hpp"

CTexture::~CTexture()
{
	if( glIsTexture( GLID ) )
	{
		glDeleteTextures( 1, &GLID );
	}
}

void CTexture::BindToUnit( const GLuint unit ) const
{
	CGLState::BindTextureToUnit( GLID, unit );
}

void CTexture::Reset()
{
	if( glIsTexture( GLID ) )
	{
		glDeleteTextures( 1, &GLID );
	}

	GLID = 0;
}