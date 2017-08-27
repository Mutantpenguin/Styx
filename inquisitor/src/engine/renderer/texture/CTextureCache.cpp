#include "CTextureCache.hpp"

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"


CTextureCache::CTextureCache( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	CResourceCache( "texture", p_filesystem ),
	m_textureLoader( p_settings, p_filesystem, openGlAdapter )
{
}

void CTextureCache::LoadFromFile( const std::string &path, const std::shared_ptr< CTexture > &resource )
{
	m_textureLoader.FromFile( path, resource );
}
