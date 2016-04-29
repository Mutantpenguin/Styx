#include "CUniformBuffer.hpp"

CUniformBuffer::CUniformBuffer( const GLsizei size, const void *data, const GLenum usage, const EUniformBufferLocation location, const std::string &placeholder, const std::string &source ) :
	m_placeholder { placeholder },
	m_source { source }
{
	glCreateBuffers( 1, &m_uniformBuffer );
	glNamedBufferData( m_uniformBuffer, size, data, usage );

	glBindBufferBase( GL_UNIFORM_BUFFER, static_cast< std::uint16_t >( location ), m_uniformBuffer );


	size_t locationPlaceholderPosition = m_source.find( locationPlaceholder );
	if( std::string::npos != locationPlaceholderPosition )
	{
		m_source.replace( locationPlaceholderPosition, locationPlaceholder.length(), std::to_string( static_cast< std::uint16_t >( location ) ) );
	}
}

CUniformBuffer::~CUniformBuffer()
{
	glDeleteBuffers( 1, &m_uniformBuffer );
}

void CUniformBuffer::SubData( const GLintptr offset, const GLsizei size, const void *data )
{
	glNamedBufferSubData( m_uniformBuffer, offset, size, data );
}

const std::string &CUniformBuffer::Placeholder( void ) const
{
	return( m_placeholder );
}

const std::string &CUniformBuffer::Source( void ) const
{
	return( m_source );
}
