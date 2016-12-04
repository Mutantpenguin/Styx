#ifndef CSHADERPROGRAM_HPP
#define CSHADERPROGRAM_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include "../GL.h"

#include "EReservedUniformLocations.hpp"
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
	std::vector< EReservedUniformLocations >		m_requiredReservedUniforms;
	std::unordered_map< GLint, SShaderInterface >	m_requiredInstanceUniforms;
};

#endif // CSHADERPROGRAM_HPP
