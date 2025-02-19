#include "src/resource/CResourceCacheBase.hpp"

#include "src/logger/CLogger.hpp"

CResourceCacheBase::CResourceCacheBase( const std::string &name ) :
	m_name { name }
{
	logINFO( "cache for '{0}' was initialized", m_name );
}

CResourceCacheBase::~CResourceCacheBase()
{
	logINFO( "cache for '{0}' is shutting down", m_name );
}

const std::string & CResourceCacheBase::Name() const
{
	return( m_name );
}
