#include "CUniformBuffer.hpp"

#include "src/ext/fmt/format.h"

CUniformBuffer::CUniformBuffer( const GLsizei size, const GLenum usage, const EUniformBufferLocation location, const std::string &name, const std::string &body ) :
	m_source { "layout ( std140, binding = " + std::to_string( static_cast< GLuint >( location ) ) + " ) uniform " + name + "Block { " + body + " } " + name +";" }
{
	glCreateBuffers( 1, &m_uniformBuffer );
	glNamedBufferData( m_uniformBuffer, size, nullptr, usage );

	glBindBufferBase( GL_UNIFORM_BUFFER, static_cast< GLuint >( location ), m_uniformBuffer );
}

CUniformBuffer::~CUniformBuffer()
{
	glDeleteBuffers( 1, &m_uniformBuffer );
}

void CUniformBuffer::SubData( const GLintptr offset, const GLsizei size, const void *data )
{
	glNamedBufferSubData( m_uniformBuffer, offset, size, data );
}

const std::string &CUniformBuffer::Source( void ) const
{
	return( m_source );
}
