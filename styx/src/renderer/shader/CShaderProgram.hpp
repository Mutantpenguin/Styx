#pragma once

#include <tuple>
#include <vector>

#include "src/renderer/GL.h"

#include "src/renderer/shader/EEngineUniform.hpp"
#include "src/renderer/shader/SShaderInterface.hpp"

class CShaderProgram final
{
public:
	struct ResourceIdType
	{
		std::string vertexShader;
		std::string fragmentShader;

		bool operator<( const ResourceIdType &other) const
		{
			return( std::tie( vertexShader, fragmentShader ) < std::tie( other.vertexShader, other.fragmentShader ) );
		}
		
	};

	static std::string IdToString( const ResourceIdType &id );

public:
	explicit CShaderProgram( const GLuint id );
	CShaderProgram() {};
	~CShaderProgram();

	void Use() const;

	void Reset();

	const GLuint &OpenGLID() const;

	const std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredSamplers() const;
	const std::vector< std::pair< GLint, const EEngineUniform > >	&RequiredEngineUniforms() const;
	const std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredMaterialUniforms() const;

	std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredSamplers();
	std::vector< std::pair< GLint, const EEngineUniform > >		&RequiredEngineUniforms();
	std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredMaterialUniforms();

private:
	GLuint m_id;

	std::vector< std::pair< GLint, const SShaderInterface > >	m_requiredSamplers;
	std::vector< std::pair< GLint, const EEngineUniform > >		m_requiredEngineUniforms;
	std::vector< std::pair< GLint, const SShaderInterface > >	m_requiredMaterialUniforms;
};
