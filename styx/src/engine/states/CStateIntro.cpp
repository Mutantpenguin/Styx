#include "CStateIntro.hpp"

#include "src/engine/states/CStateMainMenu.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/components/camera/CCameraFreeComponent.hpp"
#include "src/engine/renderer/components/CModelComponent.hpp"

CStateIntro::CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface ) :
	CState( "intro", filesystem, settings, engineInterface ),
	m_startTime { m_timer.Time() },
	m_introSound { std::make_shared< CSoundSource>( engineInterface.ResourceCacheManager.GetResource< CSoundBuffer >( "sounds/startup_sound.ogg" ) ) },
	m_introDuration { m_introSound->Buffer()->Duration() * 1000000 }
{
	m_scene.ClearColor( CColor( 1.0f, 1.0f, 1.0f, 1.0f ) );

	auto &resourceCache = m_engineInterface.ResourceCacheManager;

	auto &renderer = m_engineInterface.Renderer;

	{
		auto cameraEntity = m_scene.CreateEntity( "free camera" );
		cameraEntity->Transform.Position( { 0.0f, 0.0f, 5.0f } );
		cameraEntity->Transform.Direction( { 0.0f, 0.0f, -10.0f } );
		cameraEntity->Add<CCameraFreeComponent>( m_settings.renderer.window.aspect_ratio, 110.0f, 0.1f, 100.0f );

		m_scene.Camera( cameraEntity );
	}

	const auto material = resourceCache.GetResource< CMaterial >( "materials/intro_icon.mat" );

	const CMesh::TMeshTextureSlots logoMeshTextureSlots = { { "diffuseTexture", std::make_shared< CMeshTextureSlot >( resourceCache.GetResource< CTexture >( "textures/styx/logo.png" ), renderer.SamplerManager().GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };

	const auto logoMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material, logoMeshTextureSlots );

	m_logoEntity = m_scene.CreateEntity( "logo" );
	m_logoEntity->Transform.Scale( { 3.0f, 3.0f, 1.0f } );
	m_logoEntity->Add<CModelComponent>( logoMesh );

	m_introSound->Play();
	m_introSound->SetRelativePositioning( true );
}

CStateIntro::~CStateIntro()
{
}

std::shared_ptr< CState > CStateIntro::OnUpdate( void )
{
	const u64 elapsedTime = m_timer.Time() - m_startTime;

	glm::vec3 entityPosition = m_logoEntity->Transform.Position();
	entityPosition.z = elapsedTime / m_introDuration;
	entityPosition.y = elapsedTime / m_introDuration;
	m_logoEntity->Transform.Position( entityPosition );

	const float fadeDuration = m_introDuration * 0.66666f ;
	const float colorComponent = ( fadeDuration - elapsedTime ) / fadeDuration;
	m_scene.ClearColor( CColor( colorComponent, colorComponent, colorComponent, colorComponent ) );

	if( ( elapsedTime > m_introDuration )
		||
		m_engineInterface.Input.KeyDown( SDL_SCANCODE_ESCAPE )
		||
		m_engineInterface.Input.KeyDown( SDL_SCANCODE_SPACE )
		||
		m_engineInterface.Input.KeyDown( SDL_SCANCODE_RETURN )
		||
		m_engineInterface.Input.MouseDown( SDL_BUTTON_LEFT ) )
	{
		try
		{
			return( std::make_shared< CStateMainMenu >( m_filesystem, m_settings, m_engineInterface ) );
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
