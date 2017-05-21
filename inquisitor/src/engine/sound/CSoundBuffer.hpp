#ifndef CSOUNDBUFFER_HPP
#define CSOUNDBUFFER_HPP

#include <cstdint>

#include <AL/al.h>
#include <AL/alc.h>

class CSoundBuffer final
{
	friend class CSoundBufferLoader;
	friend class CSoundManager;
	friend class CSoundSource;

private:
	CSoundBuffer(const CSoundBuffer& rhs);
	CSoundBuffer& operator=(const CSoundBuffer& rhs);

public:
	CSoundBuffer();
	~CSoundBuffer();

	enum struct format : std::uint8_t
	{
		MONO,
		STEREO
	};

	format Format( void ) const;
	float Duration( void ) const;

private:
	void Reset( void );

	ALuint m_bufferID;

	format	m_format;
	float	m_duration;
};

#endif // CSOUNDBUFFER_HPP
