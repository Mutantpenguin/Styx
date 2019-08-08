#pragma once

#include "src/core/Types.hpp"

#include "src/renderer/GL.h"

class CShader final
{
private:
	CShader( const CShader& rhs );
	CShader & operator = ( const CShader& rhs );

public:
	enum struct EType : u8
	{
		VERTEX = 0,
		FRAGMENT
	};

	CShader() {};
	~CShader();

	void Reset();

	GLuint GLID = 0;
};