#include "CSoundBufferCache.hpp"

CSoundBufferCache::CSoundBufferCache( const CFileSystem &filesystem ) :
	CResourceCache( "sound", filesystem ),
	m_soundBufferloader { filesystem }
{
}

void CSoundBufferCache::Load( const std::shared_ptr< CSoundBuffer > &resource, const std::string &path )
{
	m_soundBufferloader.FromFile( resource, path );
}
