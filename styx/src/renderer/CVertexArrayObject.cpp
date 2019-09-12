#include "src/renderer/CVertexArrayObject.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/CGLState.hpp"

#include "src/renderer/AttributeLocation.hpp"

// we need the values of those enums further down quite a few times
static const auto attributeLocationPosition		= static_cast<GLint>( AttributeLocation::position );
static const auto attributeLocationNormal		= static_cast<GLint>( AttributeLocation::normal );
static const auto attributeLocationTangent		= static_cast<GLint>( AttributeLocation::tangent );
static const auto attributeLocationBitangent	= static_cast<GLint>( AttributeLocation::bitangent );
static const auto attributeLocationColor		= static_cast<GLint>( AttributeLocation::color );
static const auto attributeLocationUV0			= static_cast<GLint>( AttributeLocation::uv0 );
static const auto attributeLocationUV1			= static_cast<GLint>( AttributeLocation::uv1 );
static const auto attributeLocationUV2			= static_cast<GLint>( AttributeLocation::uv2 );
static const auto attributeLocationUV3			= static_cast<GLint>( AttributeLocation::uv3 );

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexP> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );
	
	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition, 3, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions, m_vbo.GLID, offsetof( VertexPNU0, Position ), geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition, CVertexArrayObject::bindingIndexPositions );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPN> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );
	
	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,	3, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPN, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexNormals,		m_vbo.GLID, offsetof( VertexPN, Normal ),	geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVertexArrayObject::bindingIndexNormals );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPU0> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );
	
	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV0 );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV0,			2, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPU0, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV0,			m_vbo.GLID, offsetof( VertexPU0, UV0 ),			geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVertexArrayObject::bindingIndexUV0 );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPCU0> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );
	
	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationColor );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV0 );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationColor,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV0,			2, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPCU0, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexColors,	m_vbo.GLID, offsetof( VertexPCU0, Color ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV0,		m_vbo.GLID, offsetof( VertexPCU0, UV0 ),		geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationColor,		CVertexArrayObject::bindingIndexColors );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVertexArrayObject::bindingIndexUV0 );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPNU0> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );
	
	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV0 );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV0,			2, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPNU0, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexNormals,	m_vbo.GLID, offsetof( VertexPNU0, Normal ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV0,		m_vbo.GLID, offsetof( VertexPNU0, UV0 ),		geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVertexArrayObject::bindingIndexNormals );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVertexArrayObject::bindingIndexUV0 );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPNTB> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );

	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );
	glEnableVertexArrayAttrib( GLID, attributeLocationTangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationBitangent );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTangent,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationBitangent,	3, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPNTB, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexNormals,		m_vbo.GLID, offsetof( VertexPNTB, Normal ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexTangents,	m_vbo.GLID, offsetof( VertexPNTB, Tangent ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexBitangents,	m_vbo.GLID, offsetof( VertexPNTB, Bitangent ),	geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVertexArrayObject::bindingIndexNormals );
	glVertexArrayAttribBinding( GLID, attributeLocationTangent,		CVertexArrayObject::bindingIndexTangents );
	glVertexArrayAttribBinding( GLID, attributeLocationBitangent,	CVertexArrayObject::bindingIndexBitangents );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPNTBU0> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );

	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

	glEnableVertexArrayAttrib( GLID, attributeLocationPosition );
	glEnableVertexArrayAttrib( GLID, attributeLocationNormal );
	glEnableVertexArrayAttrib( GLID, attributeLocationTangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationBitangent );
	glEnableVertexArrayAttrib( GLID, attributeLocationUV0 );

	glVertexArrayAttribFormat( GLID, attributeLocationPosition,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationNormal,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationTangent,		3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationBitangent,	3, GL_FLOAT, GL_FALSE, 0 );
	glVertexArrayAttribFormat( GLID, attributeLocationUV0,			2, GL_FLOAT, GL_FALSE, 0 );

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,	m_vbo.GLID, offsetof( VertexPNTBU0, Position ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexNormals,		m_vbo.GLID, offsetof( VertexPNTBU0, Normal ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexTangents,	m_vbo.GLID, offsetof( VertexPNTBU0, Tangent ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexBitangents,	m_vbo.GLID, offsetof( VertexPNTBU0, Bitangent ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV0,			m_vbo.GLID, offsetof( VertexPNTBU0, UV0 ),			geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVertexArrayObject::bindingIndexNormals );
	glVertexArrayAttribBinding( GLID, attributeLocationTangent,		CVertexArrayObject::bindingIndexTangents );
	glVertexArrayAttribBinding( GLID, attributeLocationBitangent,	CVertexArrayObject::bindingIndexBitangents );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVertexArrayObject::bindingIndexUV0 );
}

CVertexArrayObject::CVertexArrayObject( const Geometry<VertexPNTBCU0U1U2U3> &geometry, const GLenum usage ) :
	m_mode( geometry.Mode ),
	m_indexCount( geometry.Indices.size() ),
	m_vbo( usage, geometry.Vertices ),
	m_ibo( usage, geometry.Indices )
{
	glCreateVertexArrays( 1, &GLID );
	
	glVertexArrayElementBuffer( GLID, m_ibo.GLID );

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

	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexPositions,		m_vbo.GLID,	offsetof( VertexPNTBCU0U1U2U3, Position ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexNormals,		m_vbo.GLID,	offsetof( VertexPNTBCU0U1U2U3, Normal ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexTangents,		m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, Tangent ),	geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexBitangents,	m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, Bitangent ), geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexColors,		m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, Color ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV0,			m_vbo.GLID,	offsetof( VertexPNTBCU0U1U2U3, UV0 ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV1,			m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, UV1 ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV2,			m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, UV2 ),		geometry.Stride );
	glVertexArrayVertexBuffer( GLID, CVertexArrayObject::bindingIndexUV3,			m_vbo.GLID, offsetof( VertexPNTBCU0U1U2U3, UV3 ),		geometry.Stride );

	glVertexArrayAttribBinding( GLID, attributeLocationPosition,	CVertexArrayObject::bindingIndexPositions );
	glVertexArrayAttribBinding( GLID, attributeLocationNormal,		CVertexArrayObject::bindingIndexNormals );
	glVertexArrayAttribBinding( GLID, attributeLocationTangent,		CVertexArrayObject::bindingIndexTangents );
	glVertexArrayAttribBinding( GLID, attributeLocationBitangent,	CVertexArrayObject::bindingIndexBitangents );
	glVertexArrayAttribBinding( GLID, attributeLocationColor,		CVertexArrayObject::bindingIndexColors );
	glVertexArrayAttribBinding( GLID, attributeLocationUV0,			CVertexArrayObject::bindingIndexUV0 );
	glVertexArrayAttribBinding( GLID, attributeLocationUV1,			CVertexArrayObject::bindingIndexUV1 );
	glVertexArrayAttribBinding( GLID, attributeLocationUV2,			CVertexArrayObject::bindingIndexUV2 );
	glVertexArrayAttribBinding( GLID, attributeLocationUV3,			CVertexArrayObject::bindingIndexUV3 );
}

CVertexArrayObject::~CVertexArrayObject()
{
	if( glIsVertexArray( GLID ) )
	{
		glDeleteVertexArrays( 1, &GLID );
	}
}

void CVertexArrayObject::Bind() const
{
	CGLState::BindVertexArray( GLID );
}

void CVertexArrayObject::Draw() const
{
	glDrawElements( m_mode, m_indexCount, GL_UNSIGNED_INT, nullptr );
}
