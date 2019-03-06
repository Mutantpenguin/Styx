#include "CSoundBufferCache.hpp"

CSoundBufferCache::CSoundBufferCache( const CFileSystem &filesystem ) :
	CResourceCache( "sound", filesystem ),
	m_soundBufferloader { filesystem }
{
}
