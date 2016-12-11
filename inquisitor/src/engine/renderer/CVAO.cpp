#include "src/engine/renderer/CVAO.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"

CVAO::CVAO( GLenum Mode, const Primitives::SPrimitive &primitive ) :
	m_mode( Mode ),
	m_vertexCount( primitive.vertices.size() )
{
	assert( m_vertexCount == primitive.normals.size() && m_vertexCount == primitive.texcoords.size() );

	auto attributeLocationVertex   = static_cast< GLint >( EAttributeLocation::vertex );
	auto attributeLocationNormal   = static_cast< GLint >( EAttributeLocation::normal );
	auto attributeLocationTexcoord = static_cast< GLint >( EAttributeLocation::texcoord );

	auto vertexSize		= sizeof( decltype( primitive.vertices )::value_type );
	auto normalSize		= sizeof( decltype( primitive.normals )::value_type );
	auto texcoordSize	= sizeof( decltype( primitive.texcoords )::value_type );

	glCreateVertexArrays( 1, &m_vao );

	glEnableVertexArrayAttrib( m_vao, attributeLocationVertex );
	glEnableVertexArrayAttrib( m_vao, attributeLocationNormal );
	glEnableVertexArrayAttrib( m_vao, attributeLocationTexcoord );

	glVertexArrayAttribFormat( m_vao, attributeLocationVertex,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_vao, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_vao, attributeLocationTexcoord,	2, GL_FLOAT, GL_FALSE, 0 );

	glCreateBuffers( 1, &m_vboVertices );
	glCreateBuffers( 1, &m_vboNormals );
	glCreateBuffers( 1, &m_vboTexcoords );

	glNamedBufferData( m_vboVertices,	m_vertexCount * vertexSize,		primitive.vertices.data(),	GL_STATIC_DRAW );
	glNamedBufferData( m_vboNormals,	m_vertexCount * normalSize,		primitive.normals.data(),	GL_STATIC_DRAW );
	glNamedBufferData( m_vboTexcoords,	m_vertexCount * texcoordSize,	primitive.texcoords.data(),	GL_STATIC_DRAW );

	glVertexArrayVertexBuffer( m_vao, CVAO::bindingIndexVertices,	m_vboVertices,	0, vertexSize );
	glVertexArrayVertexBuffer( m_vao, CVAO::bindingIndexNormals,	m_vboNormals,	0, normalSize );
	glVertexArrayVertexBuffer( m_vao, CVAO::bindingIndexTexcoords,	m_vboTexcoords,	0, texcoordSize );

	glVertexArrayAttribBinding( m_vao, attributeLocationVertex,		CVAO::bindingIndexVertices );
	glVertexArrayAttribBinding( m_vao, attributeLocationNormal,		CVAO::bindingIndexNormals );
	glVertexArrayAttribBinding( m_vao, attributeLocationTexcoord,	CVAO::bindingIndexTexcoords );
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
