#pragma once

#include <vector>

#include "src/renderer/GL.h"

class CBO final
{
public:
	template<typename T>
	CBO( const typename std::vector<T> &vector )
	{
		glCreateBuffers( 1, &GLID );

		glNamedBufferData( GLID, vector.size() * sizeof(T), vector.data(), GL_STATIC_DRAW );
	}
	
	~CBO();

	GLuint GLID;
};