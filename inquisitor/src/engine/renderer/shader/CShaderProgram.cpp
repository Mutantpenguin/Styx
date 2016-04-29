#include "CShaderProgram.hpp"

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
