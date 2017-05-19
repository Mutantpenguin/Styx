#ifndef CSOUND_HPP
#define CSOUND_HPP

#include <memory>
#include <vector>

class CSound
{
public:
	using TSoundData = std::vector< std::int16_t >;

	enum struct format : std::uint8_t
	{
		MONO,
		STEREO
	};
public:
	CSound( const TSoundData &soundData, const format format, const std::int32_t frequency, float duration );
	~CSound( void );

	const TSoundData &SoundData( void ) const;

	format Format( void ) const;
	std::int32_t Frequency( void ) const;
	float Duration( void ) const;

private:
	// TODO shouldn't this be a pointer?
	const TSoundData	m_soundData;

	const format		m_format;
	const std::int32_t	m_frequency;

	const float	m_duration;
};

#endif // CSOUND_HPP
