#include "CUniformBuffer.hpp"

#include "external/fmt/format.h"

CUniformBuffer::CUniformBuffer( const GLsizei size, const GLenum usage, const EUniformBufferLocation location, const std::string &name, const std::string &body ) :
	m_source { "layout ( std140, binding = " + std::to_string( static_cast<GLuint>( location ) ) + " ) uniform " + name + "Block { " + body + " } " + name +";" }
{
	glCreateBuffers( 1, &m_id );
	glNamedBufferData( m_id, size, nullptr, usage );

	glBindBufferBase( GL_UNIFORM_BUFFER, static_cast<GLuint>( location ), m_id );
}

CUniformBuffer::~CUniformBuffer()
{
	glDeleteBuffers( 1, &m_id );
}

void CUniformBuffer::SubData( const GLintptr offset, const GLsizei size, const void *data )
{
	glNamedBufferSubData( m_id, offset, size, data );
}

const std::string &CUniformBuffer::Source() const
{
	return( m_source );
}
