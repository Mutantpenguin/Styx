#ifndef CTEXTURE_HPP
#define CTEXTURE_HPP

#include "src/engine/helper/Types.hpp"

#include "src/engine/renderer/GL.h"

class CTexture final
{
private:
	CTexture( const CTexture& rhs );
	CTexture & operator = ( const CTexture& rhs );

public:
	enum struct TextureType : u8
	{
		TEX_2D = 0,
		TEX_CUBE_MAP,
		TEX_2D_ARRAY
	};

	CTexture( void );
	~CTexture( void );

	void BindToUnit( const GLuint unit ) const;

	TextureType Type( void ) const;
	void Type( const TextureType type );

	void Reset( void );

	GLuint &OpenGLID( void );

private:
	TextureType m_type;

	GLuint m_id;
};

#endif // CTEXTURE_HPP
