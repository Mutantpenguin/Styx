#include "CEngine.hpp"

#include "CTimer.hpp"

#include "external/minitrace/minitrace.h"

#include "src/logger/CLogger.hpp"

#include "src/states/CStateIntro.hpp"

const std::string	CEngine::m_name				{ "Styx Engine" };
const u16			CEngine::m_version_major	{ 19 };
const u16			CEngine::m_version_minor	{ 9 };
const u16			CEngine::m_version_patch	{ 0 };
const std::string	CEngine::m_status			{ "pre-alpha" };

CEngine::CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile ) :
	m_gameInfo( gameDirectory ),
	m_filesystem( argv0, m_gameInfo.GetOrganisation(), m_gameInfo.GetShortName(), m_gameInfo.GetPath(), m_gameInfo.GetAssets() ),
	m_settings( m_filesystem, settingsFile ),
	m_sdl(),
	m_window( m_settings, m_filesystem, m_gameInfo.GetName(), m_gameInfo.GetIconPath() ),
	m_renderer( m_settings, m_filesystem, m_resources ),
	m_input( m_settings, m_filesystem ),
	m_audio( m_settings, m_filesystem, m_resources ),
	m_samplerManager( m_renderer.OpenGlAdapter ),
	m_fontBuilder( m_filesystem ),
	m_textBuilder( m_samplerManager, m_renderer.ShaderCompiler, m_renderer.ShaderProgramCompiler ),
	m_engineInterface( m_resources, m_input, m_audio, m_samplerManager, m_fontBuilder, m_textBuilder, m_stats )
{
	logINFO( "engine was initialized" );
}

CEngine::~CEngine()
{
	logINFO( "engine terminated - shutting down all systems" );
}

void CEngine::Run()
{
	mtr_init( "trace.json" );

	logINFO( "" );

	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "START of main loop" );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	CTimer frameTimer;

	u64 lastUpdatedTime = frameTimer.Time();

	MTR_BEGIN( "main loop", "outer" );

	std::shared_ptr<CState> currentState = std::make_shared<CStateIntro>( m_filesystem, m_settings, m_engineInterface );

	while( currentState )
	{
		const u64 frameStartTime = frameTimer.Time();

		m_window.Update();

		m_renderer.RenderSceneToFramebuffer( currentState->Scene(), currentState->FrameBuffer(), currentState->Timer() );

		m_renderer.DisplayFramebuffer( currentState->FrameBuffer() );

		while( currentState && ( ( frameTimer.Time() - lastUpdatedTime ) > m_settings.engine.tick ) )
		{
			m_input.Update();

			MTR_BEGIN( "current state", "update" );
			currentState = currentState->Update();
			MTR_END( "current state", "update" );

			#ifdef STYX_DEBUG
				if( m_input.KeyDown( SDL_SCANCODE_F12 ) )
				{
					m_resources.Reload();
				}
			#endif

			lastUpdatedTime += m_settings.engine.tick;
		}

		// TODO maybe only collect garbage when changing states?
		m_resources.CollectGarbage();

		const u64 frameEndtime = frameTimer.Time();
		
		m_stats.frameTime = ( frameEndtime - frameStartTime );

		#ifdef STYX_DEBUG
			if( m_stats.frameTime > m_settings.engine.tick )
			{
				// a frame takes more time than m_settings.engine.tick, so we have fewer than 30fps
				logWARNING( "ATTENTION: frame-time is {0}ms", ( m_stats.frameTime / 1000.0f ) );
			}
		#endif // STYX_DEBUG
	}

	MTR_END( "main loop", "outer" );


	logINFO( "" );

	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "END of main loop" );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	mtr_flush();
	mtr_shutdown();
}

std::string CEngine::GetVersionString()
{
	// TODO somehow get the git revision in here?
	return( fmt::format( "'{0}' version {1:d}.{2:>02d}.{3:d} ({4})", m_name, m_version_major, m_version_minor, m_version_patch, m_status ) );
}
