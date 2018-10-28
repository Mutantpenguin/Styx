#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "src/engine/helper/Types.hpp"

class CSoundBuffer final
{
	friend class CSoundBufferLoader;
	friend class CSoundSource;

private:
	CSoundBuffer( const CSoundBuffer& rhs );
	CSoundBuffer & operator = ( const CSoundBuffer& rhs );

public:
	CSoundBuffer();
	~CSoundBuffer();

	enum struct format : u8
	{
		MONO,
		STEREO
	};

	format Format() const;
	float Duration() const;

	void Reset();

private:
	ALuint m_bufferID;

	format	m_format;
	float	m_duration;
};
