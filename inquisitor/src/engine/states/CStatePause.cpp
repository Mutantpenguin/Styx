#include "CStatePause.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/camera/CCameraFree.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems, std::shared_ptr< CState > state ) :
	CState( "pause", filesystem, settings, engineSystems ),
	m_state { state }
{
	{
		const auto materialPause = engineSystems.Renderer.LoadMaterial( "materials/pause_bg.mat" );
		const auto screenMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialPause );
		m_scene.AddMesh( screenMesh );
	}

	{
		const auto materialPauseText = engineSystems.Renderer.LoadMaterial( "materials/pause_text.mat" );

		auto pauseTextMeshPrimitive = Primitives::quad;

		for( auto &coord : pauseTextMeshPrimitive.vertices )
		{
			coord.x *= 0.25f;
			coord.y *= 0.25f;
			coord.z += 1.0f;
		}

		auto screenMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, pauseTextMeshPrimitive, materialPauseText );

		m_scene.AddMesh( screenMesh );
	}

	auto camera = std::make_shared< CCameraFree >( m_settings.renderer.window.aspect_ratio, 90.0f, 0.1f, 100.0f );
	camera->SetPosition( { 0.0f, 0.0f, 5.0f } );
	camera->SetDirection( { 0.0f, 0.0f, -10.0f } );

	m_scene.Camera( camera );
}

CStatePause::~CStatePause()
{
}

void CStatePause::Render( void ) const
{
	const auto &renderer = m_engineSystems.Renderer;

	renderer.Clear( true, true );

	renderer.RenderScene( m_state->Scene(), m_engineSystems.GlobalTimer );

	renderer.Clear( false, true );

	renderer.RenderScene( m_scene, m_engineSystems.GlobalTimer );
}

std::shared_ptr< CState > CStatePause::Update( void )
{
	const auto &input = m_engineSystems.Input;

	if( input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		logINFO( "returning to calling state '{0}'", m_state->Name() );
		return( m_state );
	}
	else if( input.KeyDown( SDL_SCANCODE_Q ) )
	{
		logINFO( "ESC pressed, shutting down..." );
		return( nullptr );
	}

	return( shared_from_this() );
}
