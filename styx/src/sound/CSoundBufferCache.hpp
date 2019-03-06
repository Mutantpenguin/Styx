#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/sound/CSoundBuffer.hpp"
#include "src/sound/CSoundBufferLoader.hpp"

class CSoundBufferCache final : public CResourceCache< CSoundBuffer, std::string >
{
public:
	explicit CSoundBufferCache( const CFileSystem &filesystem );

public:
	virtual void Load( const std::shared_ptr< CSoundBuffer > &resource, const std::string &id )
	{
		m_soundBufferloader.FromFile( resource, id );
	};

	const CSoundBufferLoader m_soundBufferloader;
};
