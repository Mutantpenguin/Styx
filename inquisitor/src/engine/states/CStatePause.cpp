#include "CStatePause.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/camera/CCameraFree.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems, std::shared_ptr< CState > state ) :
	CState( "pause", filesystem, settings, engineSystems ),
	m_startTime { engineSystems.GlobalTimer.Time() },
	m_pausedState { state }
{
	{
		const auto materialPause = engineSystems.Renderer.LoadMaterial( "materials/pause_bg.mat" );
		const auto screenMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialPause );
		m_scene.AddMesh( screenMesh );
	}

	{
		const auto materialPauseText = engineSystems.Renderer.LoadMaterial( "materials/pause_text.mat" );

		m_meshText = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialPauseText );
		m_meshText->SetScale( { 3.0f, 3.0f / 512.0f * 128.0f, 1.0f } );
		m_scene.AddMesh( m_meshText );
	}

	{
		auto camera = std::make_shared< CCamera >( m_settings.renderer.window.aspect_ratio, 110.0f, 0.1f, 100.0f );
		camera->SetPosition( { 0.0f, 0.0f, 5.0f } );
		camera->SetDirection( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( camera );
	}
}

CStatePause::~CStatePause()
{
}

void CStatePause::Render( void ) const
{
	const auto &renderer = m_engineSystems.Renderer;

	renderer.Clear( true, true );

	renderer.RenderScene( m_pausedState->Scene(), m_engineSystems.GlobalTimer );

	renderer.Clear( false, true );

	renderer.RenderScene( m_scene, m_engineSystems.GlobalTimer );
}

std::shared_ptr< CState > CStatePause::Update( void )
{
	auto pos = m_meshText->Position();
	pos.z = ( sin( m_engineSystems.GlobalTimer.Time() / 2000000.0 ) * 0.5f );
	m_meshText->SetPosition( pos );


	const auto &input = m_engineSystems.Input;

	if( input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		logINFO( "returning to calling state '{0}'", m_pausedState->Name() );
		return( m_pausedState );
	}
	else if( input.KeyDown( SDL_SCANCODE_Q ) )
	{
		logINFO( "ESC pressed, shutting down..." );
		return( nullptr );
	}

	return( shared_from_this() );
}
