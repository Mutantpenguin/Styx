#ifndef CSOUND_HPP
#define CSOUND_HPP

#include <memory>
#include <vector>

class CSound
{
public:
	using TSoundData = std::vector< std::uint8_t >;

	enum struct format : std::uint8_t
	{
		MONO,
		STEREO
	};
public:
	CSound( const TSoundData &soundData, format format, std::uint16_t frequency );
	~CSound( void );

	const TSoundData &SoundData( void ) const;

	format Format( void ) const;
	std::uint16_t Frequency( void ) const;

private:
	// TODO shouldn't this be a pointer?
	const TSoundData	m_soundData;

	const format		m_format;
	const std::uint16_t	m_frequency;
};

#endif // CSOUND_HPP
