#include "CStateIntro.hpp"

#include "CStateGame.hpp"

#include "src/engine/logger/CLogger.hpp"

CStateIntro::CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
	CState( "intro", filesystem, settings, engineSystems ),
	m_startTime { engineSystems.GlobalTimer.Time() },
	m_introSound { std::make_shared< CSoundSource>( engineSystems.SoundManager.LoadSoundBuffer( "sounds/startup_sound.ogg" ) ) },
	m_introDuration { m_introSound->Buffer()->Duration() * 1000000 }
{
	auto &renderer = m_engineSystems.Renderer;

	renderer.SetClearColor( CColor( 1.0f, 1.0f, 1.0f, 1.0f ) );

	auto camera = std::make_shared< CCamera >( m_settings.renderer.window.aspect_ratio, 110.0f, 0.1f, 100.0f );
	camera->SetPosition( { 0.0f, 0.0f, 5.0f } );
	camera->SetDirection( { 0.0f, 0.0f, -10.0f } );

	m_scene.Camera( camera );

	auto &soundManager = m_engineSystems.SoundManager;

	soundManager.SetListener( { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } );

	const auto material = renderer.MaterialManager().LoadMaterial( "materials/intro_icon.mat" );

	const CMesh::TTextures logoMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/styx/logo.png" ), renderer.SamplerManager().SamplerFromType( CSampler::Type::EDGE_2D ) ) } };

	m_logoMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material, logoMeshTextures );
	m_logoMesh->SetScale( { 3.0f, 3.0f, 1.0f } );

	m_scene.AddMesh( m_logoMesh );

	m_introSound->Play();
}

CStateIntro::~CStateIntro()
{
}

std::shared_ptr< CState > CStateIntro::Update( void )
{
	const std::uint64_t elapsedTime = m_engineSystems.GlobalTimer.Time() - m_startTime;

	glm::vec3 meshPosition = m_logoMesh->Position();
	meshPosition.z = elapsedTime / m_introDuration;
	meshPosition.y = elapsedTime / m_introDuration;
	m_logoMesh->SetPosition( meshPosition );

	const float fadeDuration = m_introDuration * 0.66666f ;
	const float colorComponent = ( fadeDuration - elapsedTime ) / fadeDuration;
	m_engineSystems.Renderer.SetClearColor( CColor( colorComponent, colorComponent, colorComponent, colorComponent ) );

	if( ( elapsedTime > m_introDuration )
		||
		m_engineSystems.Input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		try
		{
			return( std::make_shared< CStateGame >( m_filesystem, m_settings, m_engineSystems ) );
		}
		catch( std::exception &e )
		{
			logERROR( "couldn't setup game: {0}", e.what() );
			return( nullptr );
		}
		catch( ... )
		{
			logERROR( "couldn't setup game: UNDEFINED EXCEPTION" );
			return( nullptr );
		}
	}
	else
	{
		return( shared_from_this() );
	}
}
