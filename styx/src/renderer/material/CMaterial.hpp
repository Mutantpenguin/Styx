#pragma once

#include <memory>

#include "src/renderer/texture/CTexture.hpp"
#include "src/renderer/shader/CShaderProgram.hpp"

#include "src/renderer/material/CMaterialUniform.hpp"

class CMaterial final
{
public:
	CMaterial();
	~CMaterial();

	void Setup() const;

	bool Blending() const;
	void EnableBlending( const GLenum blendSrc, const GLenum blendDst );
	void DisableBlending();

	void EnableCulling( const GLenum mode );
	void DisableCulling();

	void PolygonMode( const GLenum polygonMode );

	const std::shared_ptr< const CShaderProgram > &Shader() const;
	void Shader( const std::shared_ptr< const CShaderProgram > &shader );

	const std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &MaterialUniforms() const;
	std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &MaterialUniforms();

	const std::string &Name() const;
	void Name( const std::string &name );

	void Reset();

private:

	std::string m_name;

	std::shared_ptr< const CShaderProgram >	m_shader;

	std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > m_materialUniforms;

	bool	m_bCullFace		{ false };
	GLenum	m_cullfaceMode	{ GL_NONE };	// GL_FRONT, GL_BACK or GL_FRONT_AND_BACK

	GLenum	m_polygonMode	{ GL_FILL };

	bool		m_blending	{ false };		// shall this stage be blended?
	GLenum		m_blendSrc	{ GL_NONE };	// GL_ONE, GL_SRC_ALPHA, etc.
	GLenum		m_blendDst	{ GL_NONE };	// GL_ONE, GL_SRC_ALPHA, etc.
};
