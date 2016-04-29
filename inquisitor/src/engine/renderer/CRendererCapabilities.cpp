#include "CRendererCapabilities.hpp"

#include <glbinding/Meta.h>
#include <glbinding/ContextInfo.h>

#include "../logger/CLogger.hpp"

void CRendererCapabilities::Init( void )
{
	m_extensions = glbinding::ContextInfo::extensions();
}

bool CRendererCapabilities::isSupported( const gl::GLextension extension ) const
{
	if( m_extensions.find( extension ) != m_extensions.end() )
	{
		LOG( logINFO ) << glbinding::Meta::getString( extension ) << " is available";
		return( true );
	}
	else
	{
		LOG( logWARNING ) << glbinding::Meta::getString( extension ) << " is NOT available";
		return( false );
	}
}
