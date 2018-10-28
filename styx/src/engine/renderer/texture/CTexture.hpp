#pragma once

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

	CTexture();
	~CTexture();

	void BindToUnit( const GLuint unit ) const;

	TextureType Type() const;
	void Type( const TextureType type );

	void Reset();

	GLuint &OpenGLID();

private:
	TextureType m_type;

	GLuint m_id;
};
