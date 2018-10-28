#include "src/engine/resource/CResourceCacheBase.hpp"

#include "src/engine/logger/CLogger.hpp"

CResourceCacheBase::CResourceCacheBase( const std::string &name ) :
	m_name { name }
{
	logINFO( "cache for '{0}' was initialized", m_name );
}

CResourceCacheBase::~CResourceCacheBase()
{
	logINFO( "cache for '{0}' is shutting down", m_name );
}

const std::string & CResourceCacheBase::Name()
{
	return( m_name );
}
