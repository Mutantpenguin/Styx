#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/sound/CSoundBuffer.hpp"
#include "src/sound/CSoundBufferLoader.hpp"

class CSoundBufferCache final : public CResourceCache< CSoundBuffer >
{
public:
	CSoundBufferCache( const CFileSystem &filesystem ) :
		CResourceCache( "sound", filesystem ),
		m_soundBufferloader{ filesystem }
	{}

public:
	virtual void Load( const std::shared_ptr< CSoundBuffer > &resource, const CSoundBuffer::ResourceIdType &id ) const override
	{
		m_soundBufferloader.FromFile( resource, id );
	};

	i64 GetMtime( const CSoundBuffer::ResourceIdType &id ) const override
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

	const CSoundBufferLoader m_soundBufferloader;
};
