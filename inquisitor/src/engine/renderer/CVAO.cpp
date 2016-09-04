#include "CVAO.hpp"

#include "../logger/CLogger.hpp"

#include "CGLState.hpp"

#include "shader/CShaderManager.hpp"

constexpr const GLint CVAO::attributeLocationVertex;
constexpr const GLint CVAO::attributeLocationNormal;
constexpr const GLint CVAO::attributeLocationTexcoord;

CVAO::CVAO( GLenum Mode, const Primitives::SPrimitive &primitive ) :
	m_mode( Mode ),
	m_vertexCount( primitive.vertices.size() )
{
	assert( m_vertexCount == primitive.normals.size() && m_vertexCount == primitive.coordinates.size() );

	glCreateVertexArrays( 1, &m_vao );

	glEnableVertexArrayAttrib( m_vao, CVAO::attributeLocationVertex );
	glEnableVertexArrayAttrib( m_vao, CVAO::attributeLocationNormal );
	glEnableVertexArrayAttrib( m_vao, CVAO::attributeLocationTexcoord );

	glVertexArrayAttribFormat( m_vao, CVAO::attributeLocationVertex,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_vao, CVAO::attributeLocationNormal,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_vao, CVAO::attributeLocationTexcoord,	2, GL_FLOAT, GL_FALSE, 0 );

	glCreateBuffers( 1, &m_vboVertices );
	glCreateBuffers( 1, &m_vboNormals );
	glCreateBuffers( 1, &m_vboTexcoords );

	glNamedBufferData( m_vboVertices,	m_vertexCount * sizeof( glm::vec3 ),	primitive.vertices.data(),		GL_STATIC_DRAW );
	glNamedBufferData( m_vboNormals,	m_vertexCount * sizeof( glm::vec3 ),	primitive.normals.data(),		GL_STATIC_DRAW );
	glNamedBufferData( m_vboTexcoords,	m_vertexCount * sizeof( glm::vec2 ),	primitive.coordinates.data(),	GL_STATIC_DRAW );

	glVertexArrayVertexBuffer( m_vao, CVAO::bindingIndexVertices,	m_vboVertices,	0, sizeof( glm::vec3 ) );
	glVertexArrayVertexBuffer( m_vao, CVAO::bindingIndexNormals,	m_vboNormals,	0, sizeof( glm::vec3 ) );
	glVertexArrayVertexBuffer( m_vao, CVAO::bindingIndexTexcoords,	m_vboTexcoords,	0, sizeof( glm::vec2 ) );

	glVertexArrayAttribBinding( m_vao, CVAO::attributeLocationVertex,	CVAO::bindingIndexVertices );
	glVertexArrayAttribBinding( m_vao, CVAO::attributeLocationNormal,	CVAO::bindingIndexNormals );
	glVertexArrayAttribBinding( m_vao, CVAO::attributeLocationTexcoord,	CVAO::bindingIndexTexcoords );
}

CVAO::~CVAO()
{
	if( glIsBuffer( m_vboVertices ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &m_vboVertices );
	}
	else
	{
		logERROR( "VBO for vertices is not a buffer" );
	}

	if( glIsBuffer( m_vboNormals ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &m_vboNormals );
	}
	else
	{
		logERROR( "VBO for normals is not a buffer" );
	}

	if( glIsBuffer( m_vboTexcoords ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &m_vboTexcoords );
	}
	else
	{
		logERROR( "VBO for texcoords is not a buffer" );
	}

	glDeleteVertexArrays( 1, &m_vao );
}

void CVAO::Bind( void ) const
{
	CGLState::BindVertexArray( m_vao );
}

void CVAO::Draw( void ) const
{
	glDrawArrays( m_mode, 0, m_vertexCount );
}
