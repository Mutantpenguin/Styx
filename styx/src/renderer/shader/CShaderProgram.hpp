#pragma once

#include <tuple>
#include <vector>
#include <memory>

#include "src/renderer/GL.h"

#include "src/renderer/shader/EEngineUniform.hpp"
#include "src/renderer/shader/SShaderInterface.hpp"
#include "src/renderer/shader/CShader.hpp"

class CShaderProgram final
{
public:
	CShaderProgram() {};
	~CShaderProgram();

	void Use() const;

	void Reset();

	GLuint GLID = 0;

	std::shared_ptr<const CShader>	VertexShader;
	std::shared_ptr<const CShader>	GeometryShader;
	std::shared_ptr<const CShader>	FragmentShader;

	const std::vector<std::pair<GLint, const SShaderInterface>>	&RequiredSamplers() const;
	const std::vector<std::pair<GLint, const EEngineUniform>>	&RequiredEngineUniforms() const;
	const std::vector<std::pair<GLint, const SShaderInterface>>	&RequiredMaterialUniforms() const;

	void AddRequiredSampler( const GLint location, const SShaderInterface &shaderInterface );
	void AddRequiredEngineUniform( const GLint location, const EEngineUniform engineUniform );
	void AddRequiredMaterialUniform( const GLint location, const SShaderInterface &shaderInterface );

private:
	std::vector<std::pair<GLint, const SShaderInterface>>	m_requiredSamplers;
	std::vector<std::pair<GLint, const EEngineUniform>>		m_requiredEngineUniforms;
	std::vector<std::pair<GLint, const SShaderInterface>>	m_requiredMaterialUniforms;
};
