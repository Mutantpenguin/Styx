#include "CMaterial.hpp"

#include "src/engine/renderer/CGLState.hpp"

CMaterial::CMaterial( void )
{
}

CMaterial::~CMaterial( void )
{
}

void CMaterial::Setup( void ) const
{
	CGLState::CullFace( m_bCullFace, m_cullfacemode );
	CGLState::PolygonMode( m_polygonmode );
	CGLState::Blending( m_blending, m_blendSrc, m_blendDst );
}

bool CMaterial::Blending( void ) const
{
	return( m_blending );
};

const std::shared_ptr< const CShaderProgram > &CMaterial::Shader( void ) const
{
	return( m_shader );
}

const std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &CMaterial::MaterialUniforms( void ) const
{
	return( m_materialUniforms );
}

const std::string &CMaterial::Name( void ) const
{
	return( m_name );
}

void CMaterial::Reset( void )
{
	m_name = "";

	m_shader = nullptr;

	m_materialUniforms.clear();

	m_bCullFace		= false;
	m_cullfacemode	= GL_NONE;

	m_polygonmode	= GL_FILL;

	m_blending	= false;
	m_blendSrc	= GL_NONE;
	m_blendDst	= GL_NONE;
}
