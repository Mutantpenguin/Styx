#include "CShaderProgram.hpp"

#include "src/engine/renderer/CGLState.hpp"

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

void CShaderProgram::Use( void ) const
{
	CGLState::UseProgram( m_id );
}

const GLuint &CShaderProgram::OpenGLID( void ) const
{
	return( m_id );
}

const std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredSamplers( void ) const
{
	return( m_requiredSamplers );
}

const std::vector< std::pair< GLint, const EEngineUniform > > &CShaderProgram::RequiredEngineUniforms( void ) const
{
	return( m_requiredEngineUniforms );
}

const std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredMaterialUniforms( void ) const
{
	return( m_requiredMaterialUniforms );
}

std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredSamplers( void )
{
	return( m_requiredSamplers );
}

std::vector< std::pair< GLint, const EEngineUniform > > &CShaderProgram::RequiredEngineUniforms( void )
{
	return( m_requiredEngineUniforms );
}

std::vector< std::pair< GLint, const SShaderInterface > > &CShaderProgram::RequiredMaterialUniforms( void )
{
	return( m_requiredMaterialUniforms );
}
