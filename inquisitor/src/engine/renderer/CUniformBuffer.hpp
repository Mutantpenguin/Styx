#ifndef CUNIFORMBUFFER_HPP
#define CUNIFORMBUFFER_HPP

#include "GL.h"

#include "EUniformBufferLocations.hpp"

class CUniformBuffer
{
public:
	CUniformBuffer( const GLsizei size, const void *data, const GLenum usage, const EUniformBufferLocation location, const std::string &placeholder, const std::string &source );
	~CUniformBuffer();

	void SubData( const GLintptr offset, const GLsizei size, const void *data );

	const std::string &Placeholder( void ) const;
	const std::string &Source( void ) const;

private:
	GLuint	m_uniformBuffer;

	const std::string m_placeholder;
	std::string m_source;

	const std::string locationPlaceholder = "[LOCATION]";
};

#endif // CUNIFORMBUFFER_HPP
