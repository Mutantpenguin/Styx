#include "CVBO.hpp"

CVBO::CVBO( const size_t size, const void * data )
{
	glCreateBuffers( 1, &GLID );

	glNamedBufferData( GLID, size, data, GL_STATIC_DRAW );
}

CVBO::~CVBO()
{
	if( glIsBuffer( GLID ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &GLID );
	}
}