#include "CShaderProgram.hpp"

#include "src/renderer/CGLState.hpp"

CShaderProgram::CShaderProgram( const GLuint id ) :
	m_id { id }
{
}

CShaderProgram::~CShaderProgram()
{
	if( glIsProgram( m_id ) == GL_TRUE )
	{
		glDeleteProgram( m_id );
	}
}

void CShaderProgram::Use() const
{
	CGLState::UseProgram( m_id );
}

const GLuint &CShaderProgram::OpenGLID() const
{
	return( m_id );
}

const std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredSamplers() const
{
	return( m_requiredSamplers );
}

const std::vector< std::pair< GLint, const EEngineUniform > > &CShaderProgram::RequiredEngineUniforms() const
{
	return( m_requiredEngineUniforms );
}

const std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredMaterialUniforms() const
{
	return( m_requiredMaterialUniforms );
}

std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredSamplers()
{
	return( m_requiredSamplers );
}

std::vector< std::pair< GLint, const EEngineUniform > > &CShaderProgram::RequiredEngineUniforms()
{
	return( m_requiredEngineUniforms );
}

std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredMaterialUniforms()
{
	return( m_requiredMaterialUniforms );
}
