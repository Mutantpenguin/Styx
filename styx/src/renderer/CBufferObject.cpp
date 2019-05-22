#include "CBufferObject.hpp"

CBufferObject::~CBufferObject()
{
	if( glIsBuffer( GLID ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &GLID );
	}
}