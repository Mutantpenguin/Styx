#include "CRendererCapabilities.hpp"

#include <glbinding/Meta.h>
#include <glbinding/ContextInfo.h>

#include "src/engine/logger/CLogger.hpp"

void CRendererCapabilities::Init( void )
{
	m_extensions = glbinding::ContextInfo::extensions();
}

bool CRendererCapabilities::isSupported( const gl::GLextension extension ) const
{
	if( m_extensions.find( extension ) != m_extensions.end() )
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
