#include "CRendererCapabilities.hpp"

#include <glbinding/ContextInfo.h>

CRendererCapabilities::CRendererCapabilities( void ) :
	m_extensions { glbinding::ContextInfo::extensions() }
{
	// TODO query all capabilities in this class
}

bool CRendererCapabilities::isSupported( const gl::GLextension extension ) const
{
	if( m_extensions.find( extension ) != std::end( m_extensions ) )
	{
		return( true );
	}
	else
	{
		return( false );
	}
}
