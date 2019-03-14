#include "CShaderProgram.hpp"

#include "external/fmt/format.h"

#include "src/renderer/CGLState.hpp"

std::string CShaderProgram::IdToString( const ResourceIdType &id )
{
	return( fmt::format( "{0} / {1} / {2}", id.vertexShader, id.geometryShader, id.fragmentShader ) );
}

CShaderProgram::~CShaderProgram()
{
	if( glIsProgram( GLID ) == GL_TRUE )
	{
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
