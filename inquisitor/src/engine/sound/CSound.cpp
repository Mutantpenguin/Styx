#include "CSound.hpp"

CSound::CSound( const TSoundData &soundData, format format, std::uint64_t frequency ) :
	m_soundData { soundData },
	m_format { format },
	m_frequency { frequency }
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

std::uint64_t CSound::Frequency( void ) const
{
	return( m_frequency );
}
