#include "CShaderProgram.hpp"

#include "src/engine/renderer/CGLState.hpp"

CShaderProgram::CShaderProgram( GLuint program ) :
	m_program { program }
{
}

CShaderProgram::~CShaderProgram()
{
	if( glIsProgram( m_program ) == GL_TRUE )
	{
		glDeleteProgram( m_program );
	}
}

void CShaderProgram::Use( void ) const
{
	CGLState::UseProgram( m_program );
}

const std::unordered_map< GLint, SShaderInterface > CShaderProgram::RequiredSamplers( void ) const
{
	return( m_requiredSamplers );
}

const std::unordered_map< GLint, EEngineUniform > CShaderProgram::RequiredEngineUniforms( void ) const
{
	return( m_requiredEngineUniforms );
}

const std::unordered_map< GLint, SShaderInterface > CShaderProgram::RequiredMaterialUniforms( void ) const
{
	return( m_requiredMaterialUniforms );
}
