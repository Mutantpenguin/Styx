#pragma once

#include "src/renderer/GL.h"

#include "src/renderer/EUniformBufferLocations.hpp"

class CUniformBuffer
{
public:
	CUniformBuffer( const GLsizei size, const GLenum usage, const EUniformBufferLocation location, const std::string &name, const std::string &body );
	~CUniformBuffer();

	void SubData( const GLintptr offset, const GLsizei size, const void *data );

	const std::string &Source() const;

private:
	GLuint	m_id;

	const std::string m_source;
};
