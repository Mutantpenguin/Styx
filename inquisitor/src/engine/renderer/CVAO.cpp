#include "src/engine/renderer/CVAO.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"

CVAO::CVAO( GLenum Mode, const Primitives::SPrimitive &primitive ) :
	m_mode( Mode ),
	m_vertexCount( primitive.vertices.size() )
{
	assert( ( m_vertexCount == primitive.normals.size() ) && ( m_vertexCount == primitive.texcoords.size() ) );

	const auto attributeLocationVertex   = static_cast< GLint >( EAttributeLocation::vertex );
	const auto attributeLocationNormal   = static_cast< GLint >( EAttributeLocation::normal );
	const auto attributeLocationTexcoord = static_cast< GLint >( EAttributeLocation::texcoord );

	const auto vertexSize	= sizeof( decltype( primitive.vertices )::value_type );
	const auto normalSize	= sizeof( decltype( primitive.normals )::value_type );
	const auto texcoordSize	= sizeof( decltype( primitive.texcoords )::value_type );

	glCreateVertexArrays( 1, &m_id );

	glEnableVertexArrayAttrib( m_id, attributeLocationVertex );
	glEnableVertexArrayAttrib( m_id, attributeLocationNormal );
	glEnableVertexArrayAttrib( m_id, attributeLocationTexcoord );

	glVertexArrayAttribFormat( m_id, attributeLocationVertex,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTexcoord,	2, GL_FLOAT, GL_FALSE, 0 );

	glCreateBuffers( 1, &m_vboVertices );
	glCreateBuffers( 1, &m_vboNormals );
	glCreateBuffers( 1, &m_vboTexcoords );

	glNamedBufferData( m_vboVertices,	m_vertexCount * vertexSize,		primitive.vertices.data(),	GL_STATIC_DRAW );
	glNamedBufferData( m_vboNormals,	m_vertexCount * normalSize,		primitive.normals.data(),	GL_STATIC_DRAW );
	glNamedBufferData( m_vboTexcoords,	m_vertexCount * texcoordSize,	primitive.texcoords.data(),	GL_STATIC_DRAW );

	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexVertices,	m_vboVertices,	0, vertexSize );
	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexNormals,	m_vboNormals,	0, normalSize );
	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTexcoords,	m_vboTexcoords,	0, texcoordSize );

	glVertexArrayAttribBinding( m_id, attributeLocationVertex,		CVAO::bindingIndexVertices );
	glVertexArrayAttribBinding( m_id, attributeLocationNormal,		CVAO::bindingIndexNormals );
	glVertexArrayAttribBinding( m_id, attributeLocationTexcoord,	CVAO::bindingIndexTexcoords );
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

	glDeleteVertexArrays( 1, &m_id );
}

void CVAO::Bind( void ) const
{
	CGLState::BindVertexArray( m_id );
}

void CVAO::Draw( void ) const
{
	glDrawArrays( m_mode, 0, m_vertexCount );
}
