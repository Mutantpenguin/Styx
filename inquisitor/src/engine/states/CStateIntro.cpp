#include "CStateIntro.hpp"

#include "CStateGame.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "../sound/CSound.hpp"
#include "../sound/SoundHandler.hpp"

CStateIntro::CStateIntro( const CFileSystem &filesystem, const CSettings &settings, const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer ) :
	CState( "intro", filesystem, settings ),
	m_startTime { time }
{
	renderer.SetClearColor( CColor( 1.0f, 1.0f, 1.0f, 1.0f ) );

	const CSize &windowSize = m_settings.renderer.window.size;

	const float aspectRatio = static_cast< float >( windowSize.width ) / static_cast< float >( windowSize.height );

	auto cameraFree = std::make_shared< CCameraFree >( aspectRatio, 90.0f, 0.1f, 100.0f );
	cameraFree->SetPosition( { 0.0f, 0.0f, 5.0f } );
	cameraFree->SetDirection( { 0.0f, 0.0f, -10.0f } );

	m_scene.Camera( cameraFree );

	soundManager.SetListener( cameraFree );

	std::shared_ptr< CMaterial > material = renderer.LoadMaterial( "materials/intro_icon.mat" );

	m_mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material );
	m_mesh->SetScale( { 3.0f, 3.0f, 1.0f } );
	m_scene.AddMesh( m_mesh );

	// TODO port to SoundManager or something like this
	// TODO don't loop sound
	//std::shared_ptr< CSound > blah = SoundHandler::Load( m_filesystem, "sounds/startup_sound.ogg" );
	//soundManager.Play( blah );
}

CStateIntro::~CStateIntro()
{
}

std::shared_ptr< CState > CStateIntro::Update( const std::uint64_t time, CSoundManager& soundManager, CRenderer& renderer, const CInput& input )
{
	const std::uint64_t elapsedTime = time - m_startTime;

	glm::vec3 meshPosition = m_mesh->Position();
	meshPosition.z = elapsedTime / m_waitTime;
	meshPosition.y = elapsedTime / m_waitTime;
	m_mesh->SetPosition( meshPosition );

	const float colorComponent = ( m_waitTime - elapsedTime ) / m_waitTime;
	renderer.SetClearColor( CColor( colorComponent, colorComponent, colorComponent, colorComponent ) );

	if( ( elapsedTime > m_waitTime )
		||
		input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		try
		{
			return( std::make_shared< CStateGame >( m_filesystem, m_settings, soundManager, renderer ) );
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
