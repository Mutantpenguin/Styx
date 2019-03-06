#include "CTextureCache.hpp"

#include "src/logger/CLogger.hpp"


CTextureCache::CTextureCache( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	CResourceCache( "texture", p_filesystem ),
	m_textureLoader( p_settings, p_filesystem, openGlAdapter )
{
}
