#include "CBO.hpp"

CBO::~CBO()
{
	if( glIsBuffer( GLID ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &GLID );
	}
}