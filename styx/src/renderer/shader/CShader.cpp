#include "CShader.hpp"

CShader::~CShader()
{
	glDeleteShader( GLID );
}