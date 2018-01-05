#include "CEngine.hpp"
#include "CTimer.hpp"

#include "src/ext/minitrace/minitrace.h"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/states/CStateIntro.hpp"

const std::string CEngine::m_name				{ "Inquisitor Engine" };
const std::uint16_t CEngine::m_version_major	{ 17 };
const std::uint16_t CEngine::m_version_minor	{ 8 };
const std::uint16_t CEngine::m_version_patch	{ 0 };
const std::string CEngine::m_status				{ "pre-alpha" };

CEngine::CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile )
	try :
		m_gameInfo( gameDirectory ),
		m_filesystem( argv0, m_gameInfo.GetOrganisation(), m_gameInfo.GetShortName(), m_gameInfo.GetDir(), m_gameInfo.GetAssets() ),
		m_settings( m_filesystem, settingsFile ),
		m_sdl(),
		m_window( m_settings, m_filesystem, m_gameInfo.GetName(), m_gameInfo.GetIconPath() ),
		m_engineInterface( m_settings, m_filesystem ),
		m_currentState { std::make_shared< CStateIntro >( m_filesystem, m_settings, m_engineInterface ) }
{
	logINFO( "engine was initialized" );
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
	logINFO( "engine terminated - shutting down all systems" );
}


void CEngine::Run( void )
{
	mtr_init( "trace.json" );

	logINFO( "" );

	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "START of main loop" );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	CTimer renderTimer;

	std::uint64_t lastUpdatedTime = renderTimer.Time();

	#ifdef INQ_DEBUG
		std::uint64_t lastTime = renderTimer.Time();
	#endif

	MTR_BEGIN( "main", "outer" );

	while( m_currentState )
	{
		#ifdef INQ_DEBUG
			lastTime = renderTimer.Time();
		#endif

		m_window.Update();

		m_engineInterface.Renderer.RenderSceneToFramebuffer( m_currentState->Scene(), m_currentState->FrameBuffer(), m_currentState->Timer() );

		m_engineInterface.Renderer.DisplayFramebuffer( m_currentState->FrameBuffer() );

		while( m_currentState && ( ( renderTimer.Time() - lastUpdatedTime ) > m_settings.engine.tick ) )
		{
			m_engineInterface.Input.Update();

			MTR_BEGIN( "state", "update" );
			m_currentState = m_currentState->Update();
			MTR_END( "state", "update" );

			#ifdef INQ_DEBUG
				if( m_engineInterface.Input.KeyDown( SDL_SCANCODE_F12 ) )
				{
					m_engineInterface.ResourceCacheManager.Reload();
				}
			#endif

			lastUpdatedTime += m_settings.engine.tick;
		}

		// TODO maybe only collect garbage when changing states?
		m_engineInterface.ResourceCacheManager.CollectGarbage();

		#ifdef INQ_DEBUG
			const float deltaTime = ( renderTimer.Time() - lastTime );
			if( deltaTime > m_settings.engine.tick )
			{
				// a frame takes more time than m_settings.engine.tick, so we have fewer than 30fps
				logWARNING( "ATTENTION: frame-time is {0}ms", ( deltaTime / 1000.0f ) );
			}
		#endif // INQ_DEBUG
	}

	MTR_END( "main", "outer" );


	logINFO( "" );

	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "END of main loop" );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	mtr_flush();
	mtr_shutdown();
}

std::string CEngine::GetVersionString( void )
{
	// TODO somehow get the git revision in here?
	return( fmt::format( "'{0}' version {1:d}.{2:>02d}.{3:d} ({4})", m_name, m_version_major, m_version_minor, m_version_patch, m_status ) );
}
