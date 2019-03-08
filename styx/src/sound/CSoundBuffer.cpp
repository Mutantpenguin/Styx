#include "CSoundBuffer.hpp"

CSoundBuffer::~CSoundBuffer()
{
	if( alIsBuffer( m_bufferID ) )
	{
		alDeleteBuffers( 1, &m_bufferID );
	}
}

CSoundBuffer::format CSoundBuffer::Format() const
{
	return( m_format );
}

f16 CSoundBuffer::Duration() const
{
	return( m_duration );
}

void CSoundBuffer::Reset()
{
	if( alIsBuffer( m_bufferID ) )
	{
		alDeleteBuffers( 1, &m_bufferID );
	}

	m_bufferID = 0;
}
