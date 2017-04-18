#ifndef CSHADERPROGRAM_HPP
#define CSHADERPROGRAM_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/shader/EEngineUniform.hpp"
#include "src/engine/renderer/shader/SShaderInterface.hpp"

class CShaderProgram final
{
	friend class CShaderManager;

public:
	CShaderProgram( GLuint program );
	~CShaderProgram();

	void Use( void ) const;

	const std::unordered_map< GLint, SShaderInterface > &RequiredSamplers( void ) const;
	const std::unordered_map< GLint, EEngineUniform > &RequiredEngineUniforms( void ) const;
	const std::unordered_map< GLint, SShaderInterface > &RequiredMaterialUniforms( void ) const;

private:
	const GLuint m_program;

	std::unordered_map< GLint, SShaderInterface >	m_requiredSamplers;
	std::unordered_map< GLint, EEngineUniform >		m_requiredEngineUniforms;
	std::unordered_map< GLint, SShaderInterface >	m_requiredMaterialUniforms;
};

#endif // CSHADERPROGRAM_HPP
