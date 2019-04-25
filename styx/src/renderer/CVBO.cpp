#include "CVBO.hpp"

CVBO::CVBO( const Primitives::SPrimitive &primitive ) :
	m_vertexCount( primitive.Vertices.size() )
{
	glCreateBuffers( 1, &GLID );

	glNamedBufferData( GLID, primitive.Vertices.size() * sizeof( Primitives::SVertex ), primitive.Vertices.data(), GL_STATIC_DRAW );
}

CVBO::~CVBO()
{
	if( glIsBuffer( GLID ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &GLID );
	}
}