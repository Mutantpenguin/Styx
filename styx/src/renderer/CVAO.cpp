#include "src/renderer/CVAO.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/CGLState.hpp"

// we need the values of those enums further down quite a few times
static const auto attributeLocationPosition		= static_cast<GLint>( CVAO::EAttributeLocation::position );
static const auto attributeLocationNormal		= static_cast<GLint>( CVAO::EAttributeLocation::normal );
static const auto attributeLocationTangent		= static_cast<GLint>( CVAO::EAttributeLocation::tangent );
static const auto attributeLocationBitangent	= static_cast<GLint>( CVAO::EAttributeLocation::bitangent );
static const auto attributeLocationColor		= static_cast<GLint>( CVAO::EAttributeLocation::color );
static const auto attributeLocationUV0			= static_cast<GLint>( CVAO::EAttributeLocation::uv0 );
static const auto attributeLocationUV1			= static_cast<GLint>( CVAO::EAttributeLocation::uv1 );
static const auto attributeLocationUV2			= static_cast<GLint>( CVAO::EAttributeLocation::uv2 );
static const auto attributeLocationUV3			= static_cast<GLint>( CVAO::EAttributeLocation::uv3 );

CVAO::CVAO( GLenum Mode, const Geometry<VertexP> &geometry ) :
	m_mode( Mode ),
	m_vertexCount( geometry.Vertices.size() ),
	m_vbo( geometry.Vertices.size() * geometry.Stride, geometry.Vertices.data() )
{
	glCreateVertexArrays( 1, &GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition, 3, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexPositions, m_vbo.GLID, offsetof( VertexPNU0, Position ), geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition, CVAO::bindingIndexPositions );
}

CVAO::CVAO( GLenum Mode, const Geometry<VertexPN> &geometry ) :
	m_mode( Mode ),
	m_vertexCount( geometry.Vertices.size() ),
	m_vbo( geometry.Vertices.size() * geometry.Stride, geometry.Vertices.data() )
{
	glCreateVertexArrays( 1, &GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,	3, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPN, Position ), geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexNormals,		m_vbo.GLID, offsetof( VertexPN, Normal ),	geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVAO::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVAO::bindingIndexNormals );
}

CVAO::CVAO( GLenum Mode, const Geometry<VertexPNU0> &geometry ) :
	m_mode( Mode ),
	m_vertexCount( geometry.Vertices.size() ),
	m_vbo( geometry.Vertices.size() * geometry.Stride, geometry.Vertices.data() )
{
	glCreateVertexArrays( 1, &GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV0 );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV0,			2, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPNU0, Position ), geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexNormals,		m_vbo.GLID, offsetof( VertexPNU0, Normal ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexUV0,			m_vbo.GLID, offsetof( VertexPNU0, UV0 ),		geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVAO::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVAO::bindingIndexNormals );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVAO::bindingIndexUV0 );
}

CVAO::CVAO( GLenum Mode, const Geometry<VertexPNTBCU0U1U2U3> &geometry ) :
	m_mode( Mode ),
	m_vertexCount( geometry.Vertices.size() ),
	m_vbo( geometry.Vertices.size() * geometry.Stride, geometry.Vertices.data() )
{
	glCreateVertexArrays( 1, &GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );
	glEnableVertexArrayAttrib( GLID, attributeLocationTangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationBitangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationColor );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV0 );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV1 );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV2 );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV3 );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTangent,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationBitangent,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationColor,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV0,			2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV1,			2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV2,			2, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV3,			2, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexPositions,	m_vbo.GLID,	offsetof( VertexPNTBCU0U1U2U3, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexNormals,		m_vbo.GLID,	offsetof( VertexPNTBCU0U1U2U3, Normal ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexTangents,	m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, Tangent ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexBitangents,	m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, Bitangent ), geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexColors,		m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, Color ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexUV0,			m_vbo.GLID,	offsetof( VertexPNTBCU0U1U2U3, UV0 ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexUV1,			m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, UV1 ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexUV2,			m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, UV2 ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVAO::bindingIndexUV3,			m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, UV3 ),		geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVAO::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVAO::bindingIndexNormals );
	glVertexArrayAttribBinding( GLID, attributeLocationTangent,		CVAO::bindingIndexTangents );
	glVertexArrayAttribBinding( GLID, attributeLocationBitangent,	CVAO::bindingIndexBitangents );
	glVertexArrayAttribBinding( GLID, attributeLocationColor,		CVAO::bindingIndexColors );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVAO::bindingIndexUV0 );
	glVertexArrayAttribBinding( GLID, attributeLocationUV1,			CVAO::bindingIndexUV1 );
	glVertexArrayAttribBinding( GLID, attributeLocationUV2,			CVAO::bindingIndexUV2 );
	glVertexArrayAttribBinding( GLID, attributeLocationUV3,			CVAO::bindingIndexUV3 );
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
	glDrawArrays( m_mode, 0, m_vertexCount );
}
