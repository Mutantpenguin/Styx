#include "CResourceCacheManager.hpp"

CResourceCacheManager::CResourceCacheManager( void )
{
	logINFO( "resource cache manager was initialized" );
}

CResourceCacheManager::~CResourceCacheManager( void )
{
	logINFO( "resource cache manager is shutting down" );

	if( !m_resourceCaches.empty() )
	{
		logWARNING( "there are still '{0}' registered caches", m_resourceCaches.size() );
		#ifdef INQ_DEBUG
		for( const auto &cache : m_resourceCaches )
		{
			logDEBUG( "\t{0}:", cache->Name() );
		}
		#endif
	}
}

void CResourceCacheManager::RegisterResourceCache( const std::shared_ptr< CResourceCache > &resourceCache )
{
	const auto it = m_resourceCaches.find( resourceCache );

	if( it == std::cend( m_resourceCaches ) )
	{
		m_resourceCaches.insert( resourceCache );
	}
	else
	{
		logWARNING( "resource cache '{0}' already registered", resourceCache->Name() )
	}
}

void CResourceCacheManager::UnRegisterResourceCache( const std::shared_ptr< CResourceCache > &resourceCache )
{
	const auto it = m_resourceCaches.find( resourceCache );

	if( it == std::cend( m_resourceCaches ) )
	{
		logWARNING( "resource cache '{0}' not found", resourceCache->Name() )
	}
	else
	{
		m_resourceCaches.erase( it );
	}
}

void CResourceCacheManager::GarbageCollect( void )
{
	for( auto &resourceCache : m_resourceCaches )
	{
		resourceCache->GarbageCollect();
	}
}
