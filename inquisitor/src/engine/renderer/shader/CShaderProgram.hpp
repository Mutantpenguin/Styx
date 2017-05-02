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

	const std::unordered_map< GLint, const SShaderInterface > &RequiredSamplers( void ) const;
	const std::unordered_map< GLint, const EEngineUniform > &RequiredEngineUniforms( void ) const;
	const std::unordered_map< GLint, const SShaderInterface > &RequiredMaterialUniforms( void ) const;

private:
	const GLuint m_program;

	std::unordered_map< GLint, const SShaderInterface >	m_requiredSamplers;
	std::unordered_map< GLint, const EEngineUniform >	m_requiredEngineUniforms;
	std::unordered_map< GLint, const SShaderInterface >	m_requiredMaterialUniforms;
};

#endif // CSHADERPROGRAM_HPP
