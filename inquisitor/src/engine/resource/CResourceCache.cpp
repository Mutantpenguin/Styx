#include "src/engine/resource/CResourceCache.hpp"

#include "src/engine/logger/CLogger.hpp"

CResourceCache::CResourceCache( const std::string &name ) :
	m_name { name }
{
	logINFO( "'{0}' cache was initialized", m_name );
}

CResourceCache::~CResourceCache( void )
{
	logINFO( "'{0}' cache is shutting down", m_name );
}

const std::string & CResourceCache::Name( void )
{
	return( m_name );
}
