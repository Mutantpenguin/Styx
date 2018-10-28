#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/shader/EEngineUniform.hpp"
#include "src/engine/renderer/shader/SShaderInterface.hpp"

class CShaderProgram final
{
public:
	explicit CShaderProgram( const GLuint id );
	~CShaderProgram();

	void Use() const;

	const GLuint &OpenGLID() const;

	const std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredSamplers() const;
	const std::vector< std::pair< GLint, const EEngineUniform > >	&RequiredEngineUniforms() const;
	const std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredMaterialUniforms() const;

	std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredSamplers();
	std::vector< std::pair< GLint, const EEngineUniform > >	&RequiredEngineUniforms();
	std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredMaterialUniforms();

private:
	const GLuint m_id;

	std::vector< std::pair< GLint, const SShaderInterface > >	m_requiredSamplers;
	std::vector< std::pair< GLint, const EEngineUniform > >		m_requiredEngineUniforms;
	std::vector< std::pair< GLint, const SShaderInterface > >	m_requiredMaterialUniforms;
};
