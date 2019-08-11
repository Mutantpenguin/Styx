#include "CShaderProgram.hpp"

#include "external/fmt/format.h"

#include "src/renderer/CGLState.hpp"

CShaderProgram::~CShaderProgram()
{
	if( glIsProgram( GLID ) == GL_TRUE )
	{
		glDetachShader( GLID, VertexShader->GLID );

		if( nullptr != GeometryShader )
		{
			glDetachShader( GLID, GeometryShader->GLID );
		}

		glDetachShader( GLID, FragmentShader->GLID );

		glDeleteProgram( GLID );
	}
}

void CShaderProgram::Use() const
{
	CGLState::UseProgram( GLID );
}

void CShaderProgram::Reset()
{
	if( glIsProgram( GLID ) == GL_TRUE )
	{
		glDeleteProgram( GLID );
	}

	VertexShader = nullptr;
	GeometryShader = nullptr;
	FragmentShader = nullptr;

	m_requiredSamplers.clear();
	m_requiredEngineUniforms.clear();
	m_requiredMaterialUniforms.clear();
}

const std::vector<std::pair<GLint, const SShaderInterface>> &CShaderProgram::RequiredSamplers() const
{
	return( m_requiredSamplers );
}

const std::vector<std::pair<GLint, const EEngineUniform>> &CShaderProgram::RequiredEngineUniforms() const
{
	return( m_requiredEngineUniforms );
}

const std::vector<std::pair<GLint, const SShaderInterface>> &CShaderProgram::RequiredMaterialUniforms() const
{
	return( m_requiredMaterialUniforms );
}

void CShaderProgram::AddRequiredSampler( const GLint location, const SShaderInterface &shaderInterface )
{
	m_requiredSamplers.emplace_back( std::make_pair( location, shaderInterface ) );
}

void CShaderProgram::AddRequiredEngineUniform( const GLint location, const EEngineUniform engineUniform )
{
	m_requiredEngineUniforms.emplace_back( std::make_pair( location, engineUniform ) );
}

void CShaderProgram::AddRequiredMaterialUniform( const GLint location, const SShaderInterface &shaderInterface )
{
	m_requiredMaterialUniforms.emplace_back( std::make_pair( location, shaderInterface ) );
}
