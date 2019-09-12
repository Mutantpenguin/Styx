#pragma once

#include <vector>

#include "src/renderer/GL.h"

class CBufferObject final
{
public:
	template<typename T>
	CBufferObject( const GLenum usage ) :
		m_usage { usage }
	{
		glCreateBuffers( 1, &GLID );
	}
	
	template<typename T>
	CBufferObject( const GLenum usage, const typename std::vector<T> &vector ) :
		m_usage { usage }
	{
		glCreateBuffers( 1, &GLID );

		Data( vector );
	}

	template<typename T>
	void Data( const typename std::vector<T> &vector )
	{
		glNamedBufferData( GLID, vector.size() * sizeof( T ), vector.data(), m_usage );
	}
	
	~CBufferObject();

	GLuint GLID;

private:
	const GLenum m_usage;
};