#include "CState.hpp"

CState::CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface ) :
		m_name { name },
		m_frameBuffer( settings.renderer.window.size ),
		m_filesystem { filesystem },
		m_settings { settings },
		m_engineInterface { engineInterface }
{}

std::shared_ptr< CState > CState::Update( void )
{
	switch( m_status )
	{
		case eStatus::RUNNING:
			return( OnUpdate() );
		case eStatus::PAUSED:
			return( shared_from_this() );
	};
}

void CState::Pause( void )
{
	if( eStatus::RUNNING == m_status )
	{
		OnPause();

		m_timer.Pause();

		m_status = eStatus::PAUSED;
	};
}

void CState::Resume( void )
{
	if( eStatus::PAUSED == m_status )
	{
		OnResume();

		m_timer.Resume();

		m_status = eStatus::RUNNING;
	};
}

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

const CTimer &CState::Timer( void ) const
{
	return( m_timer );
}
