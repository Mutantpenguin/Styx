#include "CRendererCapabilities.hpp"

#include <glbinding/Meta.h>
#include <glbinding/ContextInfo.h>

#include "src/engine/logger/CLogger.hpp"

CRendererCapabilities::CRendererCapabilities( void ) :
	m_extensions { glbinding::ContextInfo::extensions() }
{
	// TODO query all capabilities in this class
}

bool CRendererCapabilities::isSupported( const gl::GLextension extension ) const
{
	if( m_extensions.find( extension ) != std::end( m_extensions ) )
	{
		logINFO( "{0} is available", glbinding::Meta::getString( extension ) );
		return( true );
	}
	else
	{
		logWARNING( "{0} is NOT available", glbinding::Meta::getString( extension ) );
		return( false );
	}
}
