#ifndef CUNIFORMBUFFER_HPP
#define CUNIFORMBUFFER_HPP

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/EUniformBufferLocations.hpp"

class CUniformBuffer
{
public:
	CUniformBuffer( const GLsizei size, const GLenum usage, const EUniformBufferLocation location, const std::string &name, const std::string &body );
	~CUniformBuffer();

	void SubData( const GLintptr offset, const GLsizei size, const void *data );

	const std::string &Source( void ) const;

private:
	GLuint	m_uniformBuffer;

	const std::string m_source;
};

#endif // CUNIFORMBUFFER_HPP
