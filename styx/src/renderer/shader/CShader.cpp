#include "CShader.hpp"

CShader::~CShader()
{
	glDeleteShader( GLID );
}

void CShader::Reset()
{
	glDeleteShader( GLID );

	GLID = 0;
}