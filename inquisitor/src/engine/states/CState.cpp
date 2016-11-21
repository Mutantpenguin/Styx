#include "CState.hpp"

CState::CState( const std::string name, const CFileSystem &filesystem, const CSettings &settings ) :
		m_name { name },
		m_filesystem { filesystem },
		m_settings { settings }
{};

void CState::Render( const CRenderer &renderer, const std::uint64_t time ) const
{
	renderer.RenderScene( m_scene, time );
}

const CScene &CState::Scene( void ) const
{
	return( m_scene );
}

const std::string &CState::Name( void ) const
{
	return( m_name );
}
