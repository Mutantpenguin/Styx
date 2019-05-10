#include "CResources.hpp"

#include <algorithm>

#include "src/logger/CLogger.hpp"

CResources::CResources()
{
	logINFO( "resource cache manager was initialized" );
}

CResources::~CResources()
{
	logINFO( "resource cache manager is shutting down" );

	#ifdef STYX_DEBUG
	if( !m_resourceCacheMap.empty() )
	{
		logWARNING( "there are still '{0}' registered caches", m_resourceCacheMap.size() );
		for( const auto &cache : m_resourceCacheMap )
		{
			logDEBUG( "\t{0}", cache.second->Name() );
		}
	}
	#endif
}

void CResources::RemoveCache( const std::shared_ptr<CResourceCacheBase> &resourceCache )
{
	const auto itMap = std::find_if( std::cbegin( m_resourceCacheMap ), std::cend( m_resourceCacheMap ), [&] ( auto &x ) { return( x.second == resourceCache ); } );

	if( itMap == std::cend( m_resourceCacheMap ) )
	{
		logWARNING( "resource cache '{0}' not found", resourceCache->Name() )
	}
	else
	{
		m_resourceCacheMap.erase( itMap );

		const auto itVec = std::find_if( std::cbegin( m_resourceCachesOrdered ), std::cend( m_resourceCachesOrdered ), [ & ]( auto &x ) { return( x == resourceCache ); } );

		m_resourceCachesOrdered.erase( itVec );
	}
}

void CResources::CollectGarbage()
{
	for( auto it = m_resourceCachesOrdered.rbegin(); it != m_resourceCachesOrdered.rend(); ++it )
	{
		(*it)->CollectGarbage();
	}
}


void CResources::Reload()
{
	for( auto &resourceCache : m_resourceCachesOrdered )
	{
		resourceCache->Reload();
	}
}
