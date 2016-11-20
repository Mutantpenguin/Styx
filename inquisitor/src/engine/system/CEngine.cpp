#include "CEngine.hpp"

#include "../logger/CLogger.hpp"

#include "../states/CStateIntro.hpp"

#include "CWindow.hpp"

const std::string CEngine::m_name		{ "Inquisitor Engine" };
const std::string CEngine::m_version	{ "16.04" };
const std::string CEngine::m_status		{ "pre-alpha" };

CEngine::CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile ) :
	m_gameInfo( gameDirectory ),
	m_filesystem( argv0, m_gameInfo.GetOrganisation(), m_gameInfo.GetShortName(), m_gameInfo.GetDir(), m_gameInfo.GetAssets() ),
	m_settings( m_filesystem, settingsFile ),
	m_sdl(),
	m_window( m_settings, m_filesystem, m_gameInfo.GetName(), m_gameInfo.GetIconPath() ),
	m_input( m_settings, m_filesystem ),
	m_renderer( m_settings, m_filesystem ),
	m_soundManager( m_settings )
{
	if( !m_soundManager.Init() )
	{
		throw std::exception();
	}

	m_currentState = std::make_shared< CStateIntro >( m_filesystem, m_settings, m_globalTimer.Time(), m_soundManager, m_renderer );
}

CEngine::~CEngine( void )
{
	logDEBUG( "engine terminated" );
}


void CEngine::Run( void )
{
	logINFO( "start main loop" );

	std::uint64_t lastUpdatedTime = m_globalTimer.Time();

	while( m_currentState )
	{
		m_globalTimer.Update();

		m_renderer.RenderScene( m_currentState->Scene(), m_globalTimer.Time() );

		m_soundManager.Update();

		#ifdef INQ_DEBUG
			if( m_globalTimer.dT() > m_settings.engine.tick )
			{
				// a frame takes more time than m_settings.engine.tick, so we have fewer than 30fps
				logWARNING( "ATTENTION: frame-time is {0}ms", m_globalTimer.dT() );
			}
		#endif // INQ_DEBUG

		const std::uint64_t currentTime = m_globalTimer.Time();
		while( ( currentTime - lastUpdatedTime ) > m_settings.engine.tick )
		{
			m_input.Update();

			m_currentState = m_currentState->Update( m_globalTimer.Time(), m_soundManager, m_renderer, m_input );

			lastUpdatedTime += m_settings.engine.tick;
		}

		m_renderer.Update( m_globalTimer.dT() );

		m_window.Update();
	}

	logINFO( "end main loop" );
}

const std::string CEngine::GetVersionString( void )
{
	// TODO somehow get the git revision in here?
	return( "'" + m_name + "' version '" + m_version + " " + m_status );
}
