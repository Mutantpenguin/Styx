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
	CGLState::CullFace( m_bCullFace, m_cullfaceMode );
	CGLState::PolygonMode( m_polygonMode );
	CGLState::Blending( m_blending, m_blendSrc, m_blendDst );

	m_shader->Use();

	for( const auto & [ location, uniform ] : m_materialUniforms )
	{
		uniform->Set( location );
	}
}

bool CMaterial::Blending( void ) const
{
	return( m_blending );
}

void CMaterial::EnableBlending( const GLenum blendSrc, const GLenum blendDst )
{
	m_blending = true;
	m_blendSrc = blendSrc;
	m_blendDst = blendDst;
}

void CMaterial::DisableBlending( void )
{
	m_blending = false;
	m_blendSrc = GL_NONE;
	m_blendDst = GL_NONE;
}

void CMaterial::EnableCulling( const GLenum mode )
{
	m_bCullFace = true;
	m_cullfaceMode = mode;
}

void CMaterial::DisableCulling( void )
{
	m_bCullFace = false;
	m_cullfaceMode = GL_NONE;
}

void CMaterial::PolygonMode( const GLenum polygonMode )
{
	m_polygonMode = polygonMode;
}

const std::shared_ptr< const CShaderProgram > &CMaterial::Shader( void ) const
{
	return( m_shader );
}

void CMaterial::Shader( const std::shared_ptr< const CShaderProgram > shader )
{
	m_shader = shader;
}

const std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &CMaterial::MaterialUniforms( void ) const
{
	return( m_materialUniforms );
}

std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &CMaterial::MaterialUniforms( void )
{
	return( m_materialUniforms );
}

const std::string &CMaterial::Name( void ) const
{
	return( m_name );
}

void CMaterial::Name( const std::string &name )
{
	m_name = name;
}

void CMaterial::Reset( void )
{
	m_name = "";

	m_shader = nullptr;

	m_materialUniforms.clear();

	m_bCullFace		= false;
	m_cullfaceMode	= GL_NONE;

	m_polygonMode	= GL_FILL;

	m_blending	= false;
	m_blendSrc	= GL_NONE;
	m_blendDst	= GL_NONE;
}
