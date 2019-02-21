#include "CTextureCache.hpp"

#include "src/logger/CLogger.hpp"


CTextureCache::CTextureCache( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	CResourceCache( "texture", p_filesystem ),
	m_textureLoader( p_settings, p_filesystem, openGlAdapter )
{
}

void CTextureCache::Load( const std::shared_ptr< CTexture > &resource, const std::string &path )
{
	m_textureLoader.FromFile( resource, path );
}
