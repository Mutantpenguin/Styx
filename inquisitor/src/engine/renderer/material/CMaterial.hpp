#ifndef CMATERIAL_HPP
#define CMATERIAL_HPP

#include <memory>
#include <vector>

#include "src/engine/renderer/texture/CTexture.hpp"
#include "CMaterialLayer.hpp"

class CMaterial final
{
friend class CRenderer;
friend class CMaterialManager;
friend class CMaterialLoader;

public:
	CMaterial( const std::string &name );
	~CMaterial( void );

	void	Update( const float delta );

	inline bool Blending( void ) const
	{
		return( m_blending );
	};

	const std::vector< std::shared_ptr< CMaterialLayer > > &Layers( void ) const;

private:
	std::shared_ptr< CMaterialLayer > CreateLayer( void );

	std::vector< std::shared_ptr< CMaterialLayer > > m_layers;

	const std::string m_name;

	bool	m_bCullFace		{ false };
	GLenum	m_cullfacemode	{ GL_NONE };	// GL_FRONT, GL_BACK or GL_FRONT_AND_BACK

	GLenum	m_polygonmode	{ GL_FILL };

	bool		m_blending	{ false };		// shall this stage be blended?
	GLenum		m_blendSrc	{ GL_NONE };	// GL_ONE, GL_SRC_ALPHA, etc.
	GLenum		m_blendDst	{ GL_NONE };	// GL_ONE, GL_SRC_ALPHA, etc.
};

#endif // CMATERIAL_HPP
