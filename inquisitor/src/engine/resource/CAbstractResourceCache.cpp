#include "src/engine/resource/CAbstractResourceCache.hpp"

#include "src/engine/logger/CLogger.hpp"

CAbstractResourceCache::CAbstractResourceCache( const std::string &name ) :
	m_name { name }
{
	logINFO( "'{0}' cache was initialized", m_name );
}

CAbstractResourceCache::~CAbstractResourceCache( void )
{
	logINFO( "'{0}' cache is shutting down", m_name );
}

const std::string & CAbstractResourceCache::Name( void )
{
	return( m_name );
}
