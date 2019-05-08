#include "CMaterial.hpp"

#include "src/renderer/CGLState.hpp"

void CMaterial::Activate() const
{
	CGLState::CullFace( m_bCullFace, m_cullfaceMode );
	CGLState::PolygonMode( m_polygonMode );
	CGLState::Blending( m_blending, m_blendSrc, m_blendDst );
	CGLState::DepthMask( m_depthMask );

	m_shaderProgram->Use();

	for( const auto & [ location, uniform ] : m_materialUniforms )
	{
		uniform->Set( location );
	}
}

bool CMaterial::Blending() const
{
	return( m_blending );
}

void CMaterial::EnableBlending( const GLenum blendSrc, const GLenum blendDst )
{
	m_blending = true;
	m_blendSrc = blendSrc;
	m_blendDst = blendDst;
}

void CMaterial::DisableBlending()
{
	m_blending = false;
	m_blendSrc = GL_NONE;
	m_blendDst = GL_NONE;
}

void CMaterial::EnableDepthMask()
{
	m_depthMask = GL_TRUE;
}

void CMaterial::DisableDepthMask()
{
	m_depthMask = GL_FALSE;
}

void CMaterial::EnableCulling( const GLenum mode )
{
	m_bCullFace = true;
	m_cullfaceMode = mode;
}

void CMaterial::DisableCulling()
{
	m_bCullFace = false;
	m_cullfaceMode = GL_NONE;
}

void CMaterial::PolygonMode( const GLenum polygonMode )
{
	m_polygonMode = polygonMode;
}

const std::shared_ptr<const CShaderProgram> &CMaterial::ShaderProgram() const
{
	return( m_shaderProgram );
}

void CMaterial::ShaderProgram( const std::shared_ptr<const CShaderProgram> &shaderProgram )
{
	m_shaderProgram = shaderProgram;
}

const std::vector<std::pair<GLuint, std::unique_ptr<const CMaterialUniform>>> &CMaterial::MaterialUniforms() const
{
	return( m_materialUniforms );
}

std::vector<std::pair<GLuint, std::unique_ptr<const CMaterialUniform>>> &CMaterial::MaterialUniforms()
{
	return( m_materialUniforms );
}

const std::string &CMaterial::Name() const
{
	return( m_name );
}

void CMaterial::Name( const std::string &name )
{
	m_name = name;
}

void CMaterial::Reset()
{
	m_name = "";

	m_shaderProgram = nullptr;

	m_materialUniforms.clear();

	m_bCullFace		= false;
	m_cullfaceMode	= GL_NONE;

	m_polygonMode	= GL_FILL;

	m_blending	= false;
	m_blendSrc	= GL_NONE;
	m_blendDst	= GL_NONE;

	m_depthMask = GL_TRUE;
}
