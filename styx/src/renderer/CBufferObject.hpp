#pragma once

#include <vector>

#include "src/renderer/GL.h"

class CBufferObject final
{
public:
	template<typename T>
	CBufferObject( const typename std::vector<T> &vector )
	{
		glCreateBuffers( 1, &GLID );

		glNamedBufferData( GLID, vector.size() * sizeof(T), vector.data(), GL_STATIC_DRAW );
	}
	
	~CBufferObject();

	GLuint GLID;
};