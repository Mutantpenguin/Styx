#include "CStateIntro.hpp"

#include "CStateGame.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/sound/CSound.hpp"
#include "src/engine/sound/CSoundLoader.hpp"

CStateIntro::CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
	CState( "intro", filesystem, settings, engineSystems ),
	m_startTime { engineSystems.GlobalTimer.Time() }
{
	auto &renderer = m_engineSystems.Renderer;

	renderer.SetClearColor( CColor( 1.0f, 1.0f, 1.0f, 1.0f ) );

	auto cameraFree = std::make_shared< CCameraFree >( m_settings.renderer.window.aspect_ratio, 135.0f, 0.1f, 100.0f );
	cameraFree->SetPosition( { 0.0f, 0.0f, 5.0f } );
	cameraFree->SetDirection( { 0.0f, 0.0f, -10.0f } );

	m_scene.Camera( cameraFree );

	auto &soundManager = m_engineSystems.SoundManager;

	m_engineSystems.SoundManager.SetListener( cameraFree );

	const auto material = renderer.LoadMaterial( "materials/intro_icon.mat" );

	m_mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material );
	m_mesh->SetScale( { 3.0f, 3.0f, 1.0f } );
	m_scene.AddMesh( m_mesh );

	// TODO don't loop sound
	const auto startupSound = m_engineSystems.SoundManager.Load( "sounds/startup_sound.ogg" );
	soundManager.Play( startupSound );
}

CStateIntro::~CStateIntro()
{
}

std::shared_ptr< CState > CStateIntro::Update( void )
{
	const std::uint64_t elapsedTime = m_engineSystems.GlobalTimer.Time() - m_startTime;

	glm::vec3 meshPosition = m_mesh->Position();
	meshPosition.z = elapsedTime / m_waitTime;
	meshPosition.y = elapsedTime / m_waitTime;
	m_mesh->SetPosition( meshPosition );

	const float colorComponent = ( m_waitTime - elapsedTime ) / m_waitTime;
	m_engineSystems.Renderer.SetClearColor( CColor( colorComponent, colorComponent, colorComponent, colorComponent ) );

	if( ( elapsedTime > m_waitTime )
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
