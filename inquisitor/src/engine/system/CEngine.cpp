#include "CEngine.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/states/CStateIntro.hpp"

#include "CWindow.hpp"

const std::string CEngine::m_name				{ "Inquisitor Engine" };
const std::uint16_t CEngine::m_version_major	{ 17 };
const std::uint16_t CEngine::m_version_minor	{ 1 };
const std::uint16_t CEngine::m_version_patch	{ 0 };
const std::string CEngine::m_status				{ "pre-alpha" };

CEngine::CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile )
	try :
		m_gameInfo( gameDirectory ),
		m_filesystem( argv0, m_gameInfo.GetOrganisation(), m_gameInfo.GetShortName(), m_gameInfo.GetDir(), m_gameInfo.GetAssets() ),
		m_settings( m_filesystem, settingsFile ),
		m_sdl(),
		m_window( m_settings, m_filesystem, m_gameInfo.GetName(), m_gameInfo.GetIconPath() ),
		m_input( m_settings, m_filesystem ),
		m_renderer( m_settings, m_filesystem ),
		m_soundManager( m_settings, m_filesystem ),
		m_currentState { std::make_shared< CStateIntro >( m_filesystem, m_settings, m_globalTimer.Time(), m_soundManager, m_renderer ) }
{
}
catch( CRenderer::Exception &e )
{
	logERROR( "unable to initialize Renderer" );
	throw std::exception();
}
catch( CSDL::Exception &e )
{
	logERROR( "unable to initialize SDL" );
	throw std::exception();
}
catch( CWindow::Exception &e )
{
	logERROR( "unable to initialize Window" );
	throw std::exception();
}
catch( CGameInfo::Exception &e )
{
	logERROR( "unable to initialize GameInfo" );
	throw std::exception();
}
catch( CFileSystem::Exception &e )
{
	logERROR( "unable to initialize Filesystem" );
	throw std::exception();
}
catch( CSoundManager::Exception &e )
{
	logERROR( "unable to initialize SoundManager" );
	throw std::exception();
}
catch( CSettings::Exception &e )
{
	logERROR( "unable to initialize Settings" );
	throw std::exception();
}

CEngine::~CEngine( void )
{
	logINFO( "engine terminated" );
}


void CEngine::Run( void )
{
	logINFO( "" );

	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "START of main loop" );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	std::uint64_t lastUpdatedTime = m_globalTimer.Time();

	while( m_currentState )
	{
		m_globalTimer.Update();

		m_window.Update();

		m_currentState->Render( m_renderer, m_globalTimer.Time() );

		m_soundManager.Update();

		const std::uint64_t currentTime = m_globalTimer.Time();
		while( m_currentState && ( currentTime - lastUpdatedTime ) > m_settings.engine.tick )
		{
			m_input.Update();

			m_currentState = m_currentState->Update( m_globalTimer.Time(), m_soundManager, m_renderer, m_input );

			lastUpdatedTime += m_settings.engine.tick;
		}

		m_renderer.Update();

		#ifdef INQ_DEBUG
			if( m_globalTimer.dT() > m_settings.engine.tick )
			{
				// a frame takes more time than m_settings.engine.tick, so we have fewer than 30fps
				logWARNING( "ATTENTION: frame-time is {0}ms", m_globalTimer.dT() );
			}
		#endif // INQ_DEBUG
	}


	logINFO( "" );

	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "END of main loop" );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );
}

std::string CEngine::GetVersionString( void )
{
	// TODO somehow get the git revision in here?
	return( fmt::format( "'{0}' version {1:d}.{2:>02d}.{3:d} ({4})", m_name, m_version_major, m_version_minor, m_version_patch, m_status ) );
}
