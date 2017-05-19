#include "CSound.hpp"

CSound::CSound( const TSoundData &soundData, const format format, const std::int32_t frequency, float duration ) :
	m_soundData { soundData },
	m_format { format },
	m_frequency { frequency },
	m_duration { duration }
{
}

CSound::~CSound( void )
{
}

const CSound::TSoundData &CSound::SoundData( void ) const
{
	return( m_soundData );
}

CSound::format CSound::Format( void ) const
{
	return( m_format );
}

std::int32_t CSound::Frequency( void ) const
{
	return( m_frequency );
}

float CSound::Duration( void ) const
{
	return( m_duration );
}
