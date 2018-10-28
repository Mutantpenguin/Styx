#pragma once

#include <memory>

#include "src/engine/renderer/texture/CTexture.hpp"
#include "src/engine/renderer/shader/CShaderProgram.hpp"

#include "src/engine/renderer/material/CMaterialUniform.hpp"

class CMaterial final
{
public:
	CMaterial( void );
	~CMaterial( void );

	void Setup( void ) const;

	bool Blending( void ) const;
	void EnableBlending( const GLenum blendSrc, const GLenum blendDst );
	void DisableBlending( void );

	void EnableCulling( const GLenum mode );
	void DisableCulling( void );

	void PolygonMode( const GLenum polygonMode );

	const std::shared_ptr< const CShaderProgram > &Shader( void ) const;
	void Shader( const std::shared_ptr< const CShaderProgram > &shader );

	const std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &MaterialUniforms( void ) const;
	std::vector< std::pair< GLuint, std::unique_ptr< const CMaterialUniform > > > &MaterialUniforms( void );

	const std::string &Name( void ) const;
	void Name( const std::string &name );

	void Reset( void );

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
