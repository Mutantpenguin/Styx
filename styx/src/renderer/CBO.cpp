#include "CBO.hpp"

/*
CBO::CBO( const size_t size, const void * data )
{
	glCreateBuffers( 1, &GLID );

	glNamedBufferData( GLID, size, data, GL_STATIC_DRAW );
}
*/

CBO::~CBO()
{
	if( glIsBuffer( GLID ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &GLID );
	}
}