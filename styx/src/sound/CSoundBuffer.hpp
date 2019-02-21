#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "src/helper/Types.hpp"

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
	f16 Duration() const;

	void Reset();

private:
	ALuint m_bufferID;

	format	m_format;
	f16		m_duration;
};
