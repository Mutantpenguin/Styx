#ifndef CSHADERPROGRAM_HPP
#define CSHADERPROGRAM_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include "../GL.h"

#include "EEngineUniform.hpp"
#include "SShaderInterface.hpp"

class CShaderProgram final
{
	friend class CRenderer;
	friend class CShaderManager;
	friend class CMaterialLoader;

public:
	CShaderProgram( GLuint program );
	~CShaderProgram();

private:
	const GLuint m_program;

	std::unordered_map< GLint, SShaderInterface >	m_requiredSamplers;
	std::unordered_map< GLint, EEngineUniform >		m_requiredEngineUniforms;
	std::unordered_map< GLint, SShaderInterface >	m_requiredMaterialUniforms;
};

#endif // CSHADERPROGRAM_HPP
