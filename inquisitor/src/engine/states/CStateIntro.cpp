#include "CStateIntro.hpp"

#include "src/engine/states/CStateMainMenu.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/camera/CCameraFree.hpp"

CStateIntro::CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
	CState( "intro", filesystem, settings, engineSystems ),
	m_startTime { engineSystems.GlobalTimer.Time() },
	m_introSound { std::make_shared< CSoundSource>( engineSystems.SoundManager.LoadSoundBuffer( "sounds/startup_sound.ogg" ) ) },
	m_introDuration { m_introSound->Buffer()->Duration() * 1000000 }
{
	m_scene.ClearColor( CColor( 1.0f, 1.0f, 1.0f, 1.0f ) );

	auto &renderer = m_engineSystems.Renderer;

	{
		auto camera = std::make_shared< CCameraFree >( "free camera", m_settings.renderer.window.aspect_ratio, 110.0f, 0.1f, 100.0f );
		camera->Transform.Position( { 0.0f, 0.0f, 5.0f } );
		camera->Transform.Direction( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( camera );
	}

	const auto material = renderer.MaterialManager().LoadMaterial( "materials/intro_icon.mat" );

	const CMesh::TTextures logoMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/styx/logo.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::EDGE_2D ) ) } };

	const auto logoMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material, glm::vec3( 3.0f, 3.0f, 1.0f ), logoMeshTextures );

	m_logoEntity = std::make_shared< CEntity >( "logo" );
	m_logoEntity->Mesh( logoMesh );

	m_scene.AddEntity( m_logoEntity );

	m_introSound->Play();
	m_introSound->SetRelativePositioning( true );
}

CStateIntro::~CStateIntro()
{
}

std::shared_ptr< CState > CStateIntro::Update( void )
{
	const std::uint64_t elapsedTime = m_engineSystems.GlobalTimer.Time() - m_startTime;

	glm::vec3 entityPosition = m_logoEntity->Transform.Position();
	entityPosition.z = elapsedTime / m_introDuration;
	entityPosition.y = elapsedTime / m_introDuration;
	m_logoEntity->Transform.Position( entityPosition );

	const float fadeDuration = m_introDuration * 0.66666f ;
	const float colorComponent = ( fadeDuration - elapsedTime ) / fadeDuration;
	m_scene.ClearColor( CColor( colorComponent, colorComponent, colorComponent, colorComponent ) );

	if( ( elapsedTime > m_introDuration )
		||
		m_engineSystems.Input.KeyDown( SDL_SCANCODE_ESCAPE )
		||
		m_engineSystems.Input.KeyDown( SDL_SCANCODE_SPACE )
		||
		m_engineSystems.Input.KeyDown( SDL_SCANCODE_RETURN )
		||
		m_engineSystems.Input.MouseDown( SDL_BUTTON_LEFT ) )
	{
		try
		{
			return( std::make_shared< CStateMainMenu >( m_filesystem, m_settings, m_engineSystems ) );
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
