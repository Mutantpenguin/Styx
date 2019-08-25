#pragma once

#include "src/core/Types.hpp"

#include "src/renderer/GL.h"

class CTexture final
{
private:
	CTexture( const CTexture& rhs );
	CTexture & operator = ( const CTexture& rhs );

public:
	CTexture() {};
	~CTexture();

	void BindToUnit( const GLuint unit ) const;

	GLenum Target;

	void Reset();

	GLuint GLID;
};
