#pragma once

#include <string>

#include <AL/al.h>
#include <AL/alc.h>

#include "src/helper/Types.hpp"

class CAudioBuffer final
{
	friend class CAudioBufferLoader;
	friend class CAudioSource;

public:
	using ResourceIdType = std::string;

	static std::string IdToString( const ResourceIdType &id )
	{
		return( id );
	}

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
