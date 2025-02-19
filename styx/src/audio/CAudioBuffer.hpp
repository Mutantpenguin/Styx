#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "src/core/Types.hpp"

class CAudioBuffer final
{
	friend class CAudioBufferLoader;
	friend class CAudioSource;

private:
	CAudioBuffer( const CAudioBuffer& rhs );
	CAudioBuffer & operator = ( const CAudioBuffer& rhs );

public:
	CAudioBuffer() {};
	~CAudioBuffer();

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
	f16		m_duration = 0.0f;
};
