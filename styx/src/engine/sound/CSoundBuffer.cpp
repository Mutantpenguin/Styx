#include "CSoundBuffer.hpp"

CSoundBuffer::CSoundBuffer()
{
}

CSoundBuffer::~CSoundBuffer()
{
	alDeleteBuffers( 1, &m_bufferID );
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
	alDeleteBuffers( 1, &m_bufferID );

	m_bufferID = 0;
}
