#include "CStateMainMenu.hpp"

#include "src/logger/CLogger.hpp"

#include "src/scene/components/camera/CCameraOrthoComponent.hpp"
#include "src/renderer/components/CModelComponent.hpp"

#include "src/states/CStateGame.hpp"

#include "src/renderer/geometry/prefabs/Quad.hpp"
#include "src/renderer/geometry/prefabs/Rectangle.hpp"

CStateMainMenu::CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface ) :
	CState( "main menu", filesystem, settings, engineInterface ),
	m_buttonChangeSound { std::make_shared<CAudioSource>( engineInterface.Resources.Get<CAudioBuffer>( "sounds/Pickup_Coin17.wav" ) ) },
	m_backgroundMusic { std::make_shared<CAudioSource>( engineInterface.Resources.Get<CAudioBuffer>( "music/Sad Robot.ogg" ) ) }
{
	m_buttonChangeSound->SetLooping( false );
	m_buttonChangeSound->SetRelativePositioning( true );

	{
		auto cameraEntity = m_scene.CreateEntity( "ortho camera" );
		cameraEntity->Transform.Position( { 0.0f, 0.0f, 500.0f } );
		cameraEntity->Transform.Direction( { 0.0f, 0.0f, -10.0f } );
		cameraEntity->Add<CCameraOrthoComponent>( m_settings.renderer.window.size, 0.1f, 1000.0f );

		m_scene.Camera( cameraEntity );
	}

	auto &resources = m_engineInterface.Resources;
	auto &samplerManager = m_engineInterface.SamplerManager;

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto material = resources.Get<CMaterial>( "materials/standard.mat" );

		auto bgGeometry = GeometryPrefabs::QuadPU0();
		bgGeometry.Vertices[ 0 ].Position.x = 0.0f;
		bgGeometry.Vertices[ 0 ].Position.y = 0.0f;
		bgGeometry.Vertices[ 1 ].Position.x = static_cast<f16>( windowSize.width );
		bgGeometry.Vertices[ 1 ].Position.y = 0.0f;
		bgGeometry.Vertices[ 2 ].Position.x = 0.0f;
		bgGeometry.Vertices[ 2 ].Position.y = static_cast<f16>( windowSize.height );
		bgGeometry.Vertices[ 3 ].Position.x = static_cast<f16>( windowSize.width );
		bgGeometry.Vertices[ 3 ].Position.y = static_cast<f16>( windowSize.height );

		const CMesh::TMeshTextureSlots bgMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( resources.Get<CTexture>( "textures/menu/background.jpg" ), samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared<CMesh>( bgGeometry, material, bgMeshTextureSlots );

		auto bg = m_scene.CreateEntity( "background" );
		bg->Add<CModelComponent>( bgMesh );
	}

	{
		const auto material = resources.Get<CMaterial>( "materials/standard_blend.mat" );

		const f16 titleWidth = windowSize.width * 0.75f;
		const f16 titleHeight = titleWidth / 4.0f;

		auto titleGeometry = GeometryPrefabs::RectanglePNU0( titleWidth, titleHeight );

		const CMesh::TMeshTextureSlots titleMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( resources.Get<CTexture>( "textures/menu/title.png" ), samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgTitleMesh = std::make_shared<CMesh>( titleGeometry, material, titleMeshTextureSlots );

		auto bgTitle = m_scene.CreateEntity( "title" );
		bgTitle->Transform.Position( { windowSize.width / 2.0f, windowSize.height - ( titleHeight / 2.0f ), 5.0f } );
		bgTitle->Add<CModelComponent>( bgTitleMesh );
	}

	const f16 buttonWidth = windowSize.width / 4.0f;
	const f16 buttonHeight = windowSize.height / 6.0f;

	auto buttonGeometry = GeometryPrefabs::RectangleP( buttonWidth, buttonHeight );

	{
		const auto greenMaterial = resources.Get<CMaterial>( "materials/green.mat" );

		const auto startMesh = std::make_shared<CMesh>( buttonGeometry, greenMaterial );

		m_startEntity = m_scene.CreateEntity( "start_button" );
		m_startEntity->Transform.Position( { windowSize.width / 2.0f, 2 * windowSize.height / 4.0f, 10.0f } );
		m_startEntity->Add<CModelComponent>( startMesh );
	}

	{
		const auto redMaterial = resources.Get<CMaterial>( "materials/red.mat" );

		const auto exitMesh = std::make_shared<CMesh>( buttonGeometry, redMaterial );

		m_exitEntity = m_scene.CreateEntity( "exit_button" );
		m_exitEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height / 4.0f, 10.0f } );
		m_exitEntity->Add<CModelComponent>( exitMesh );
	}

	m_backgroundMusic->Play();
	m_backgroundMusic->SetLooping( true );
}

CStateMainMenu::~CStateMainMenu()
{
}

std::shared_ptr<CState> CStateMainMenu::OnUpdate()
{
	const auto &input = m_engineInterface.Input;

	if( input.KeyDown( SDL_SCANCODE_RETURN ) )
	{
		switch( m_currentState )
		{
			case eMenuState::NONE:
				break;
			case eMenuState::START:
				return( std::make_shared<CStateGame>( m_filesystem, m_settings, m_engineInterface ) );
				break;
			case eMenuState::EXIT:
				return( nullptr );
				break;
		}
	}
	
	// TODO if( input.MouseDeltaX() )

	if( input.KeyDown( SDL_SCANCODE_UP )
		||
		input.KeyDown( SDL_SCANCODE_DOWN ) )
	{
		m_buttonChangeSound->Play();

		switch( m_currentState )
		{
			case eMenuState::NONE:
				m_startEntity->Transform.Scale( { 1.0f, 1.0f, 1.0f } );
				m_exitEntity->Transform.Scale( { 1.0f, 1.0f, 1.0f } );
				break;
			case eMenuState::START:
				m_startEntity->Transform.Scale( { 1.0f, 1.0f, 1.0f } );
				m_currentState = eMenuState::EXIT;
				break;
			case eMenuState::EXIT:
				m_exitEntity->Transform.Scale( { 1.0f, 1.0f, 1.0f } );
				m_currentState = eMenuState::START;
				break;
		}
	}

	{
		const f16 max = 1.05f;
		const f16 min = 1.0f;

		const f16 halfRange = (max - min) / 2.0f;

		const f16 buttonPulse = min + halfRange + sin( m_timer.Time() / 100000.0f ) * halfRange;

		const glm::vec3 buttonPulseVec3 = { buttonPulse, buttonPulse, buttonPulse };

		switch( m_currentState )
		{
			case eMenuState::NONE:
				break;
			case eMenuState::START:
				m_startEntity->Transform.Scale( buttonPulseVec3 );
				break;
			case eMenuState::EXIT:
				m_exitEntity->Transform.Scale( buttonPulseVec3 );
				break;
		}
	}

	return( shared_from_this() );
}
