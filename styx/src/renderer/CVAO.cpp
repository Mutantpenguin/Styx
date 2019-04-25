#include "src/renderer/CVAO.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/CGLState.hpp"

CVAO::CVAO( GLenum Mode, const Primitives::SPrimitive &primitive ) :
	m_mode( Mode ),
	m_vbo( primitive )
{
	static const auto attributeLocationPosition		= static_cast<GLint>( EAttributeLocation::position );
	static const auto attributeLocationNormal		= static_cast<GLint>( EAttributeLocation::normal );
	static const auto attributeLocationTangent		= static_cast<GLint>( EAttributeLocation::tangent );
	static const auto attributeLocationBitangent	= static_cast<GLint>( EAttributeLocation::bitangent );
	static const auto attributeLocationColor		= static_cast<GLint>( EAttributeLocation::color );
	static const auto attributeLocationTexcoord0	= static_cast<GLint>( EAttributeLocation::texcoord0 );
	static const auto attributeLocationTexcoord1	= static_cast<GLint>( EAttributeLocation::texcoord1 );
	static const auto attributeLocationTexcoord2	= static_cast<GLint>( EAttributeLocation::texcoord2 );
	static const auto attributeLocationTexcoord3	= static_cast<GLint>( EAttributeLocation::texcoord3 );

	glCreateVertexArrays( 1, &GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );
	glEnableVertexArrayAttrib( GLID, attributeLocationTangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationBitangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationColor );
	glEnableVertexArrayAttrib( GLID, attributeLocationTexcoord0 );
	glEnableVertexArrayAttrib( GLID, attributeLocationTexcoord1 );
	glEnableVertexArrayAttrib( GLID, attributeLocationTexcoord2);
	glEnableVertexArrayAttrib( GLID, attributeLocationTexcoord3 );
	

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTangent,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationBitangent,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationColor,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTexcoord0,	2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTexcoord1,	2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTexcoord2,	2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTexcoord3,	2, GL_FLOAT, GL_FALSE, 0 );
	

	

	

	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexPositions,	m_vbo.GLID,	offsetof( Primitives::SVertex, Position ),	sizeof( Primitives::SVertex ) );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexNormals,		m_vbo.GLID,	offsetof( Primitives::SVertex, Normal ),	sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexTangents,	m_vbo.GLID,	offsetof( Primitives::SVertex, Tangent ),	sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexBitangents,	m_vbo.GLID,	offsetof( Primitives::SVertex, Bitangent ), sizeof( Primitives::SVertex ) );
	// TODO Tangents glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexColor,		m_vbo.GLID,	offsetof( Primitives::SVertex, Color ),		sizeof( Primitives::SVertex ) );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexTexcoords0, m_vbo.GLID,	offsetof( Primitives::SVertex, TexCoord ),	sizeof( Primitives::SVertex ) );
	// TODO glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexTexcoords1,	m_vbo.GLID, offsetof( Primitives::SVertex, TexCoord ), sizeof( Primitives::SVertex ) );
	// TODO glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexTexcoords2,	m_vbo.GLID, offsetof( Primitives::SVertex, TexCoord ), sizeof( Primitives::SVertex ) );
	// TODO glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexTexcoords3,	m_vbo.GLID, offsetof( Primitives::SVertex, TexCoord ), sizeof( Primitives::SVertex ) );
	

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVAO::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVAO::bindingIndexNormals );
	// TODO Tangents glVertexArrayAttribBinding( GLID, attributeLocationTangent,		CVAO::bindingIndexTangents );
	// TODO Tangents glVertexArrayAttribBinding( GLID, attributeLocationBitangent,	CVAO::bindingIndexBitangents );
	// TODO Tangents glVertexArrayAttribBinding( GLID, attributeLocationColor,	CVAO::bindingIndexColor );
	glVertexArrayAttribBinding( GLID, attributeLocationTexcoord0, CVAO::bindingIndexTexcoords0 );
	// TODO glVertexArrayAttribBinding( GLID, attributeLocationTexcoord1, CVAO::bindingIndexTexcoords1 );
	// TODO glVertexArrayAttribBinding( GLID, attributeLocationTexcoord2, CVAO::bindingIndexTexcoords2 );
	// TODO glVertexArrayAttribBinding( GLID, attributeLocationTexcoord3, CVAO::bindingIndexTexcoords3 );
}

CVAO::~CVAO()
{
	if( glIsVertexArray( GLID ) )
	{
		glDeleteVertexArrays( 1, &GLID );
	}
}

void CVAO::Bind() const
{
	CGLState::BindVertexArray( GLID );
}

void CVAO::Draw() const
{
	glDrawArrays( m_mode, 0, m_vbo.VertexCount() );
}
