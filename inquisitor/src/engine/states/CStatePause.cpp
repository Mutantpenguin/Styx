#include "CStatePause.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/camera/CCameraFree.hpp"

#include "src/engine/states/CStateMainMenu.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems, std::shared_ptr< CState > state ) :
	CState( "pause", filesystem, settings, engineSystems ),
	m_startTime { engineSystems.GlobalTimer.Time() },
	m_pausedState { state }
{
	auto &renderer = engineSystems.Renderer;

	{
		const auto materialPause = renderer.MaterialManager().LoadMaterial( "materials/pause_bg.mat" );

		const CMesh::TTextures backgroundMeshTextures = { { "bgTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/pause/bg.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto backgroundMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialPause, backgroundMeshTextures );

		m_scene.AddMesh( backgroundMesh );
	}

	{
		const auto materialPauseText = renderer.MaterialManager().LoadMaterial( "materials/pause_text.mat" );

		const CMesh::TTextures textMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/pause/fg.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::EDGE_2D ) ) } };

		m_meshText = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialPauseText, textMeshTextures );
		m_meshText->SetScale( { 3.0f, 3.0f / 512.0f * 128.0f, 1.0f } );

		m_scene.AddMesh( m_meshText );
	}

	{
		auto camera = std::make_shared< CCameraFree >( m_settings.renderer.window.aspect_ratio, 110.0f, 0.1f, 100.0f );
		camera->SetPosition( { 0.0f, 0.0f, 5.0f } );
		camera->SetDirection( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( camera );
	}
}

CStatePause::~CStatePause()
{
}

std::shared_ptr< CState > CStatePause::Update( void )
{
	m_scene.ClearColor( CColor( 0.3f, 0.3f, 0.3f, 0.0f ) );

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
		logINFO( "ESC pressed, ending game..." );
		return( std::make_shared< CStateMainMenu >( m_filesystem, m_settings, m_engineSystems ) );
	}

	return( shared_from_this() );
}
