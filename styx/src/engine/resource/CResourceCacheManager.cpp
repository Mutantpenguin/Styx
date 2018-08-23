#include "CResourceCacheManager.hpp"

#include <algorithm>

#include "src/engine/logger/CLogger.hpp"

CResourceCacheManager::CResourceCacheManager( void )
{
	logINFO( "resource cache manager was initialized" );
}

CResourceCacheManager::~CResourceCacheManager( void )
{
	logINFO( "resource cache manager is shutting down" );

	#ifdef STYX_DEBUG
	if( !m_resourceCaches.empty() )
	{
		logWARNING( "there are still '{0}' registered caches", m_resourceCaches.size() );
		for( const auto &cache : m_resourceCaches )
		{
			logDEBUG( "\t{0}", cache.second->Name() );
		}
	}
	#endif
}

void CResourceCacheManager::DeRegister( const std::shared_ptr< CResourceCacheBase > &resourceCache )
{
	const auto it = std::find_if( std::cbegin( m_resourceCaches ), std::cend( m_resourceCaches ), [&] ( auto &x ) { return( x.second == resourceCache ); } );

	if( it == std::cend( m_resourceCaches ) )
	{
		logWARNING( "resource cache '{0}' not found", resourceCache->Name() )
	}
	else
	{
		m_resourceCaches.erase( it );
	}
}

void CResourceCacheManager::CollectGarbage( void )
{
	for( auto &resourceCache : m_resourceCaches )
	{
		resourceCache.second->CollectGarbage();
	}
}


void CResourceCacheManager::Reload( void )
{
	for( auto &resourceCache : m_resourceCaches )
	{
		resourceCache.second->Reload();
	}
}
