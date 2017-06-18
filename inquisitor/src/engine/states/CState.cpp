#include "CState.hpp"

CState::CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
		m_name { name },
		m_frameBuffer( settings.renderer.window.size ),
		m_filesystem { filesystem },
		m_settings { settings },
		m_engineSystems { engineSystems }
{}

const CScene &CState::Scene( void ) const
{
	return( m_scene );
}

const std::string &CState::Name( void ) const
{
	return( m_name );
}

const CFrameBuffer &CState::FrameBuffer( void ) const
{
	return( m_frameBuffer );
}
