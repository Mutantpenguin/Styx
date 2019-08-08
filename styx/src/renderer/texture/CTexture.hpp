#pragma once

#include "src/core/Types.hpp"

#include "src/renderer/GL.h"

class CTexture final
{
private:
	CTexture( const CTexture& rhs );
	CTexture & operator = ( const CTexture& rhs );

public:
	enum struct EType : u8
	{
		TEX_2D = 0,
		TEX_CUBE_MAP,
		TEX_2D_ARRAY
	};

	CTexture() {};
	~CTexture();

	void BindToUnit( const GLuint unit ) const;

	EType Type() const;
	void Type( const EType type );

	void Reset();

	GLuint GLID;

private:
	EType m_type;
};
