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
public:
	explicit CShaderProgram( const GLuint id );
	~CShaderProgram();

	void Use( void ) const;

	const GLuint &OpenGLID( void ) const;

	const std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredSamplers( void ) const;
	const std::vector< std::pair< GLint, const EEngineUniform > >	&RequiredEngineUniforms( void ) const;
	const std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredMaterialUniforms( void ) const;

	std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredSamplers( void );
	std::vector< std::pair< GLint, const EEngineUniform > >	&RequiredEngineUniforms( void );
	std::vector< std::pair< GLint, const SShaderInterface > >	&RequiredMaterialUniforms( void );

private:
	const GLuint m_id;

	std::vector< std::pair< GLint, const SShaderInterface > >	m_requiredSamplers;
	std::vector< std::pair< GLint, const EEngineUniform > >		m_requiredEngineUniforms;
	std::vector< std::pair< GLint, const SShaderInterface > >	m_requiredMaterialUniforms;
};

#endif // CSHADERPROGRAM_HPP
