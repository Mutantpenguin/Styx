#ifndef CTEXTURE_HPP
#define CTEXTURE_HPP

#include <memory>

#include "../GL.h"

#include "CCubemapData.hpp"
#include "C2DArrayData.hpp"

#include "../../helper/image/CImage.hpp"

class CTexture final
{
friend class CTextureManager;
friend class CMaterialManager;

public:
	enum struct type : std::uint8_t
	{
		TEX_2D = 0,
		TEX_CUBE_MAP,
		TEX_2D_ARRAY
	};

public:
	CTexture( const std::shared_ptr< const CImage > &image );
	CTexture( std::unique_ptr< CCubemapData > cubemapData );
	CTexture( std::unique_ptr< C2DArrayData > arrayData );
	~CTexture( void );

	void BindToUnit( const GLuint unit ) const;

	type Type( void ) const;

private:
	const type m_type;

	GLuint	m_texID;
};

#endif // CTEXTURE_HPP
