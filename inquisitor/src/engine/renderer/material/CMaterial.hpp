#ifndef CMATERIAL_HPP
#define CMATERIAL_HPP

#include <memory>

#include "src/engine/renderer/texture/CTexture.hpp"
#include "src/engine/renderer/shader/CShaderProgram.hpp"

#include "src/engine/renderer/material/CMaterialUniform.hpp"

class CMaterial final
{
friend class CMaterialLoader;
friend class CMaterialManager;

public:
	CMaterial( void );
	~CMaterial( void );

	void Setup( void ) const;

	bool Blending( void ) const;

	const std::shared_ptr< const CShaderProgram > &Shader( void ) const;

	const std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &MaterialUniforms( void ) const;

	const std::string &Name( void ) const;

private:
	void Reset( void );

	std::string m_name;

	std::shared_ptr< const CShaderProgram >	m_shader;

	std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > m_materialUniforms;

	bool	m_bCullFace		{ false };
	GLenum	m_cullfacemode	{ GL_NONE };	// GL_FRONT, GL_BACK or GL_FRONT_AND_BACK

	GLenum	m_polygonmode	{ GL_FILL };

	bool		m_blending	{ false };		// shall this stage be blended?
	GLenum		m_blendSrc	{ GL_NONE };	// GL_ONE, GL_SRC_ALPHA, etc.
	GLenum		m_blendDst	{ GL_NONE };	// GL_ONE, GL_SRC_ALPHA, etc.
};

#endif // CMATERIAL_HPP
