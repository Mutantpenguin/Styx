#ifndef CSOUNDBUFFERCACHE_HPP
#define CSOUNDBUFFERCACHE_HPP

#include "src/engine/resource/CResourceCache.hpp"

#include "src/engine/sound/CSoundBuffer.hpp"
#include "src/engine/sound/CSoundBufferLoader.hpp"

class CSoundBufferCache final : public CResourceCache< CSoundBuffer >
{
public:
	explicit CSoundBufferCache( const CFileSystem &filesystem );

public:
	virtual void LoadFromFile( const std::shared_ptr< CSoundBuffer > &resource, const std::string &path );

	const CSoundBufferLoader m_soundBufferloader;
};

#endif // CSOUNDBUFFERCACHE_HPP
