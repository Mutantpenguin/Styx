#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/sound/CSoundBuffer.hpp"
#include "src/sound/CSoundBufferLoader.hpp"

class CSoundBufferCache final : public CResourceCache< CSoundBuffer >
{
public:
	explicit CSoundBufferCache( const CFileSystem &filesystem );

public:
	virtual void Load( const std::shared_ptr< CSoundBuffer > &resource, const CSoundBuffer::ResourceIdType &id ) const override
	{
		m_soundBufferloader.FromFile( resource, id );
	};

	i64 GetMtime( const CSoundBuffer::ResourceIdType &id ) const override
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

	std::string GetIdAsString( const typename CSoundBuffer::ResourceIdType &id ) override
	{
		return( id );
	}

	const CSoundBufferLoader m_soundBufferloader;
};
