#include "CSoundBuffer.hpp"

CSoundBuffer::CSoundBuffer()
{
}

CSoundBuffer::~CSoundBuffer()
{
	alDeleteBuffers( 1, &m_bufferID );
}

CSoundBuffer::format CSoundBuffer::Format( void ) const
{
	return( m_format );
}

float CSoundBuffer::Duration( void ) const
{
	return( m_duration );
}

void CSoundBuffer::Reset( void )
{
	alDeleteBuffers( 1, &m_bufferID );

	m_bufferID = 0;
}
