#include "CState.hpp"

CState::CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
		m_name { name },
		m_filesystem { filesystem },
		m_settings { settings },
		m_engineSystems { engineSystems }
{};

void CState::Render( void ) const
{
	m_engineSystems.Renderer.Clear( true, true );

	m_engineSystems.Renderer.RenderScene( m_scene, m_engineSystems.GlobalTimer );
}

const CScene &CState::Scene( void ) const
{
	return( m_scene );
}

const std::string &CState::Name( void ) const
{
	return( m_name );
}
