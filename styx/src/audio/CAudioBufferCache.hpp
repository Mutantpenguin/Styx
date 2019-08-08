#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/audio/CAudioBuffer.hpp"
#include "src/audio/CAudioBufferLoader.hpp"

class CAudioBufferCache final : public CResourceCache<CAudioBuffer>
{
public:
	CAudioBufferCache( const CFileSystem &filesystem ) :
		CResourceCache( "audio", filesystem ),
		m_audioBufferLoader{ filesystem }
	{}

public:
	virtual void Load( const std::shared_ptr<CAudioBuffer> &resource, const std::string &id ) const override
	{
		m_audioBufferLoader.FromFile( resource, id );
	};

	const CAudioBufferLoader m_audioBufferLoader;
};
