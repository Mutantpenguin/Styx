#ifndef CRESOURCECACHEMANAGER_HPP
#define CRESOURCECACHEMANAGER_HPP

#include <set>

#include "src/engine/resource/CFileResourceCache.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/renderer/texture/CTextureLoader.hpp"

class CResourceCacheManager
{
private:
	CResourceCacheManager( const CResourceCacheManager& rhs );
	CResourceCacheManager& operator = ( const CResourceCacheManager& rhs );

public:
	CResourceCacheManager( void );
	~CResourceCacheManager( void );

	void RegisterResourceCache( const std::shared_ptr< CAbstractResourceCache > &resourceCache );
	void UnRegisterResourceCache( const std::shared_ptr< CAbstractResourceCache > &resourceCache );

	void GarbageCollect( void );

	std::set< std::shared_ptr< CAbstractResourceCache > > m_resourceCaches;
};

#endif // CRESOURCECACHEMANAGER_HPP
