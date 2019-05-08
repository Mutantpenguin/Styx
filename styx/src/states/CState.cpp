#include "CState.hpp"

CState::CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface ) :
		m_name { name },
		m_frameBuffer( settings.renderer.window.size ),
		m_filesystem { filesystem },
		m_settings { settings },
		m_engineInterface { engineInterface }
{}

std::shared_ptr<CState> CState::Update()
{
	switch( m_status )
	{
		case eStatus::RUNNING:
			return( OnUpdate() );

		case eStatus::PAUSED:
			return( shared_from_this() );

		default:
			throw std::runtime_error( fmt::format( "unknown status '{0}' for state '{1}'", static_cast<u8>( m_status ), m_name ) );
	};
}

void CState::Pause()
{
	if( eStatus::RUNNING == m_status )
	{
		OnPause();

		m_timer.Pause();

		m_status = eStatus::PAUSED;
	};
}

void CState::Resume()
{
	if( eStatus::PAUSED == m_status )
	{
		OnResume();

		m_timer.Resume();

		m_status = eStatus::RUNNING;
	};
}

const CScene &CState::Scene() const
{
	return( m_scene );
}

const std::string &CState::Name() const
{
	return( m_name );
}

const CFrameBuffer &CState::FrameBuffer() const
{
	return( m_frameBuffer );
}

const CTimer &CState::Timer() const
{
	return( m_timer );
}
