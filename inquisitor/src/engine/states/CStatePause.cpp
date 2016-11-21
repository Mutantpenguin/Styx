#include "CStatePause.hpp"

#include "../logger/CLogger.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CRenderer &renderer, std::shared_ptr< CState > state ) :
	CState( "pause", filesystem, settings ),
	m_state { state }
{
	std::shared_ptr< CMaterial > material3 = renderer.LoadMaterial( "materials/pause.mat" );

	std::shared_ptr< CMesh > screenMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material3, glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) );
	m_scene.AddMesh( screenMesh );

	std::shared_ptr< CCamera > camera = std::make_shared< CCamera >( m_settings.renderer.window.aspect_ratio, 90.0f, 0.1f, 100.0f, glm::vec3( 0.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, -10.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

	m_scene.Camera( camera );

	camera->LookAt( screenMesh->Position() );
}

CStatePause::~CStatePause()
{
}

void CStatePause::Render( const CRenderer &renderer, const std::uint64_t time ) const
{
	renderer.RenderScene( m_state->Scene(), time );

	renderer.Clear( false, true );

	renderer.RenderScene( m_scene, time );
}

std::shared_ptr< CState > CStatePause::Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input )
{
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
