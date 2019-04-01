#include "src/renderer/CVAO.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/CGLState.hpp"

CVAO::CVAO( GLenum Mode, const Primitives::SPrimitive &primitive ) :
	m_mode( Mode ),
	m_vertexCount( primitive.Vertices.size() )
{
	const auto attributeLocationPosition	= static_cast<GLint>( EAttributeLocation::position );
	const auto attributeLocationNormal		= static_cast<GLint>( EAttributeLocation::normal );
	const auto attributeLocationTangent		= static_cast<GLint>( EAttributeLocation::tangent );
	const auto attributeLocationBitangent	= static_cast<GLint>( EAttributeLocation::bitangent );
	const auto attributeLocationColor		= static_cast<GLint>( EAttributeLocation::color );
	const auto attributeLocationTexcoord0	= static_cast<GLint>( EAttributeLocation::texcoord0 );
	const auto attributeLocationTexcoord1	= static_cast<GLint>( EAttributeLocation::texcoord1 );
	const auto attributeLocationTexcoord2	= static_cast<GLint>( EAttributeLocation::texcoord2 );
	const auto attributeLocationTexcoord3	= static_cast<GLint>( EAttributeLocation::texcoord3 );

	glCreateVertexArrays( 1, &m_id );

	glEnableVertexArrayAttrib( m_id, attributeLocationPosition );
	glEnableVertexArrayAttrib( m_id, attributeLocationNormal );
	glEnableVertexArrayAttrib( m_id, attributeLocationTangent );
	glEnableVertexArrayAttrib( m_id, attributeLocationBitangent );
	glEnableVertexArrayAttrib( m_id, attributeLocationColor );
	glEnableVertexArrayAttrib( m_id, attributeLocationTexcoord0 );
	glEnableVertexArrayAttrib( m_id, attributeLocationTexcoord1 );
	glEnableVertexArrayAttrib( m_id, attributeLocationTexcoord2);
	glEnableVertexArrayAttrib( m_id, attributeLocationTexcoord3 );
	

	glVertexArrayAttribFormat( m_id, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTangent,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationBitangent,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationColor,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTexcoord0,	2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTexcoord1,	2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTexcoord2,	2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( m_id, attributeLocationTexcoord3,	2, GL_FLOAT, GL_FALSE, 0 );
	

	glCreateBuffers( 1, &m_vboId );

	glNamedBufferData( m_vboId, primitive.Vertices.size() * sizeof( Primitives::SVertex ), primitive.Vertices.data(), GL_STATIC_DRAW );

	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexPositions,	m_vboId,	offsetof( Primitives::SVertex, Position ),	sizeof( Primitives::SVertex ) );
	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexNormals,		m_vboId,	offsetof( Primitives::SVertex, Normal ),	sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTangents,	m_vboId,	offsetof( Primitives::SVertex, Tangent ),	sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexBitangents,	m_vboId,	offsetof( Primitives::SVertex, Bitangent ), sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexColor,		m_vboId,	offsetof( Primitives::SVertex, Color ),		sizeof( Primitives::SVertex ) );
	glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTexcoords0,	m_vboId,	offsetof( Primitives::SVertex, TexCoord ),	sizeof( Primitives::SVertex ) );
	// TODO glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTexcoords1,	m_vboId, offsetof( Primitives::SVertex, TexCoord ), sizeof( Primitives::SVertex ) );
	// TODO glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTexcoords2,	m_vboId, offsetof( Primitives::SVertex, TexCoord ), sizeof( Primitives::SVertex ) );
	// TODO glVertexArrayVertexBuffer( m_id, CVAO::bindingIndexTexcoords3,	m_vboId, offsetof( Primitives::SVertex, TexCoord ), sizeof( Primitives::SVertex ) );
	

	glVertexArrayAttribBinding( m_id, attributeLocationPosition,	CVAO::bindingIndexPositions );
	glVertexArrayAttribBinding( m_id, attributeLocationNormal,		CVAO::bindingIndexNormals );
	// TODO Tangents glVertexArrayAttribBinding( m_id, attributeLocationTangent,		CVAO::bindingIndexTangents );
	// TODO Tangents glVertexArrayAttribBinding( m_id, attributeLocationBitangent,	CVAO::bindingIndexBitangents );
	// TODO Tangents glVertexArrayAttribBinding( m_id, attributeLocationColor,	CVAO::bindingIndexColor );
	glVertexArrayAttribBinding( m_id, attributeLocationTexcoord0, CVAO::bindingIndexTexcoords0 );
	// TODO glVertexArrayAttribBinding( m_id, attributeLocationTexcoord1, CVAO::bindingIndexTexcoords1 );
	// TODO glVertexArrayAttribBinding( m_id, attributeLocationTexcoord2, CVAO::bindingIndexTexcoords2 );
	// TODO glVertexArrayAttribBinding( m_id, attributeLocationTexcoord3, CVAO::bindingIndexTexcoords3 );
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

	if( glIsVertexArray( m_id ) )
	{
		glDeleteVertexArrays( 1, &m_id );
	}
}

void CVAO::Bind() const
{
	CGLState::BindVertexArray( m_id );
}

void CVAO::Draw() const
{
	glDrawArrays( m_mode, 0, m_vertexCount );
}
