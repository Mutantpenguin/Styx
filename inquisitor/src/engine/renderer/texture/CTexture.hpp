#ifndef CTEXTURE_HPP
#define CTEXTURE_HPP

#include <memory>

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/texture/CCubemapData.hpp"
#include "src/engine/renderer/texture/C2DArrayData.hpp"

#include "src/engine/helper/image/CImage.hpp"

class CTexture final
{
	friend class CTextureLoader;

public:
	enum struct type : std::uint8_t
	{
		TEX_2D = 0,
		TEX_CUBE_MAP,
		TEX_2D_ARRAY
	};

public:
	// TODO split into 3 different classes?
	CTexture( const std::shared_ptr< const CImage > &image );
	CTexture( const std::unique_ptr< const CCubemapData > cubemapData );
	CTexture( const std::unique_ptr< const C2DArrayData > arrayData );
	~CTexture( void );

	void BindToUnit( const GLuint unit ) const;

	type Type( void ) const;

private:
	const type m_type;

	GLuint	m_texID;
};

#endif // CTEXTURE_HPP
