#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/sound/CSoundBuffer.hpp"
#include "src/sound/CSoundBufferLoader.hpp"

class CSoundBufferCache final : public CResourceCache< CSoundBuffer >
{
public:
	explicit CSoundBufferCache( const CFileSystem &filesystem );

public:
	virtual void LoadFromFile( const std::shared_ptr< CSoundBuffer > &resource, const std::string &path );

	const CSoundBufferLoader m_soundBufferloader;
};
