#include "src/engine/renderer/CVAO.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"

CVAO::CVAO( GLenum Mode, const Primitives::SPrimitive &primitive ) :
	m_mode( Mode ),
	m_vertexCount( primitive.Vertices.size() )
{
	const auto attributeLocationPosition	= static_cast< GLint >( EAttributeLocation::position );
	const auto attributeLocationNormal		= static_cast< GLint >( EAttributeLocation::normal );
	const auto attributeLocationTexcoord	= static_cast< GLint >( EAttributeLocation::texcoord );
	const auto attributeLocationTangent		= static_cast< GLint >( EAttributeLocation::tangent );
	const auto attributeLocationBitangent	= static_cast< GLint >( EAttributeLocation::bitangent );

	glCreateVertexArrays( 1, &m_id );

	glEnableVertexArrayAttrib( m_id, attributeLocationPosition );
	glEnableVertexArrayAttrib( m_id, attributeLocationNormal );
	glEnableVertexArrayAttrib( m_id, attributeLocationTexcoord );
	glEnableVertexArrayAttrib( m_id, attributeLocationTangent );
	glEnableVertexArrayAttrib( m_id, attributeLocationBitangent );

	glVertexArrayAttribFormat( m_id, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTexcoord,		2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTangent,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationBitangent,	3, GL_FLOAT, GL_FALSE, 0 );

	glCreateBuffers( 1, &m_vboId );

	glNamedBufferData( m_vboId, primitive.Vertices.size() * sizeof( Primitives::SVertex ), primitive.Vertices.data(), GL_STATIC_DRAW );

	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexPositions,	m_vboId,	offsetof( Primitives::SVertex, Position ),	sizeof( Primitives::SVertex ) );
	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexNormals,		m_vboId,	offsetof( Primitives::SVertex, Normal ),	sizeof( Primitives::SVertex ) );
	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTexcoords,	m_vboId,	offsetof( Primitives::SVertex, TexCoord ),	sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTangents,	m_vboId,	offsetof( Primitives::SVertex, Tangent ),	sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexBitangents,	m_vboId,	offsetof( Primitives::SVertex, Bitangent ), sizeof( Primitives::SVertex ) );

	glVertexArrayAttribBinding( m_id, attributeLocationPosition,	CVAO::bindingIndexPositions );
	glVertexArrayAttribBinding( m_id, attributeLocationNormal,		CVAO::bindingIndexNormals );
	glVertexArrayAttribBinding( m_id, attributeLocationTexcoord,	CVAO::bindingIndexTexcoords );
	// TODO Tangents glVertexArrayAttribBinding( m_id, attributeLocationTangent,		CVAO::bindingIndexTangents );
	// TODO Tangents glVertexArrayAttribBinding( m_id, attributeLocationBitangent,	CVAO::bindingIndexBitangents );
}

CVAO::~CVAO()
{
	if( glIsBuffer( m_vboId ) == GL_TRUE )
	{
		glDeleteBuffers( 1, &m_vboId );
	}
	else
	{
		logERROR( "VBO is not a buffer" );
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
