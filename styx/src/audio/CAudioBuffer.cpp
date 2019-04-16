#include "CAudioBuffer.hpp"

CAudioBuffer::~CAudioBuffer()
{
	if( alIsBuffer( m_bufferID ) )
	{
		alDeleteBuffers( 1, &m_bufferID );
	}
}

CAudioBuffer::format CAudioBuffer::Format() const
{
	return( m_format );
}

f16 CAudioBuffer::Duration() const
{
	return( m_duration );
}

void CAudioBuffer::Reset()
{
	if( alIsBuffer( m_bufferID ) )
	{
		alDeleteBuffers( 1, &m_bufferID );
	}

	m_bufferID = 0;
}
