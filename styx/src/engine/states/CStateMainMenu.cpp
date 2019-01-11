#include "CStateMainMenu.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/components/camera/CCameraOrthoComponent.hpp"
#include "src/engine/renderer/components/CModelComponent.hpp"

#include "src/engine/states/CStateGame.hpp"

CStateMainMenu::CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface ) :
	CState( "main menu", filesystem, settings, engineInterface ),
	m_buttonChangeSound { std::make_shared< CSoundSource>( engineInterface.ResourceCacheManager.GetResource< CSoundBuffer >( "sounds/Pickup_Coin17.wav" ) ) }
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

	auto &renderer = m_engineInterface.Renderer;
	auto &resourceCache = m_engineInterface.ResourceCacheManager;
	auto &samplerManager = renderer.SamplerManager();

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto material = resourceCache.GetResource< CMaterial >( "materials/standard.mat" );

		auto bgMeshPrimitive = Primitives::quad;
		bgMeshPrimitive.Vertices[ 0 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 0 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 1 ].Position.x = static_cast< f16 >( windowSize.width );
		bgMeshPrimitive.Vertices[ 1 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.y = static_cast< f16 >( windowSize.height );
		bgMeshPrimitive.Vertices[ 3 ].Position.x = static_cast< f16 >( windowSize.width );
		bgMeshPrimitive.Vertices[ 3 ].Position.y = static_cast< f16 >( windowSize.height );

		const CMesh::TMeshTextureSlots bgMeshTextureSlots = { { "diffuseTexture", std::make_shared< CMeshTextureSlot >( resourceCache.GetResource< CTexture >( "textures/menu/background.jpg" ), samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, bgMeshPrimitive, material, bgMeshTextureSlots );

		auto bg = m_scene.CreateEntity( "background" );
		bg->Add<CModelComponent>( bgMesh );
	}

	{
		const auto material = resourceCache.GetResource< CMaterial >( "materials/standard_blend.mat" );

		const f16 halfTitleWidth = windowSize.width * 0.75f / 2;
		const f16 halfTitleHeight = halfTitleWidth / 4.0f;

		auto titleMeshPrimitive = Primitives::quad;
		titleMeshPrimitive.Vertices[ 0 ].Position.x = -halfTitleWidth;
		titleMeshPrimitive.Vertices[ 0 ].Position.y = -halfTitleHeight;
		titleMeshPrimitive.Vertices[ 1 ].Position.x = halfTitleWidth;
		titleMeshPrimitive.Vertices[ 1 ].Position.y = -halfTitleHeight;
		titleMeshPrimitive.Vertices[ 2 ].Position.x = -halfTitleWidth;
		titleMeshPrimitive.Vertices[ 2 ].Position.y = halfTitleHeight;
		titleMeshPrimitive.Vertices[ 3 ].Position.x = halfTitleWidth;
		titleMeshPrimitive.Vertices[ 3 ].Position.y = halfTitleHeight;

		const CMesh::TMeshTextureSlots titleMeshTextureSlots = { { "diffuseTexture", std::make_shared< CMeshTextureSlot >( resourceCache.GetResource< CTexture >( "textures/menu/title.png" ), samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgTitleMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, titleMeshPrimitive, material, titleMeshTextureSlots );

		auto bgTitle = m_scene.CreateEntity( "title" );
		bgTitle->Transform.Position( { windowSize.width / 2.0f, windowSize.height - halfTitleHeight, 5.0f } );
		bgTitle->Add<CModelComponent>( bgTitleMesh );
	}

	const f16 halfButtonWidth = windowSize.width / 4.0f / 2.0f;
	const f16 halfButtonHeight = windowSize.height / 6.0f / 2.0f;

	auto buttonMeshPrimitive = Primitives::quad;
	buttonMeshPrimitive.Vertices[ 0 ].Position.x = -halfButtonWidth;
	buttonMeshPrimitive.Vertices[ 0 ].Position.y = -halfButtonHeight;
	buttonMeshPrimitive.Vertices[ 1 ].Position.x = halfButtonWidth;
	buttonMeshPrimitive.Vertices[ 1 ].Position.y = -halfButtonHeight;
	buttonMeshPrimitive.Vertices[ 2 ].Position.x = -halfButtonWidth;
	buttonMeshPrimitive.Vertices[ 2 ].Position.y = halfButtonHeight;
	buttonMeshPrimitive.Vertices[ 3 ].Position.x = halfButtonWidth;
	buttonMeshPrimitive.Vertices[ 3 ].Position.y = halfButtonHeight;

	{
		const auto greenMaterial = resourceCache.GetResource< CMaterial >( "materials/green.mat" );

		const auto startMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, buttonMeshPrimitive, greenMaterial );

		m_startEntity = m_scene.CreateEntity( "start_button" );
		m_startEntity->Transform.Position( { windowSize.width / 2.0f, 2 * windowSize.height / 4.0f, 10.0f } );
		m_startEntity->Add<CModelComponent>( startMesh );
	}

	{
		const auto redMaterial = resourceCache.GetResource< CMaterial >( "materials/red.mat" );

		const auto exitMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, buttonMeshPrimitive, redMaterial );

		m_exitEntity = m_scene.CreateEntity( "exit_button" );
		m_exitEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height / 4.0f, 10.0f } );
		m_exitEntity->Add<CModelComponent>( exitMesh );
	}

	m_backgroundMusic = std::make_shared< CSoundSource >( resourceCache.GetResource< CSoundBuffer >( "music/Sad Robot.ogg" ) );
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
			case eMenuState::START:
				return( std::make_shared< CStateGame >( m_filesystem, m_settings, m_engineInterface ) );
				break;
			case eMenuState::EXIT:
				return( nullptr );
				break;
		}
	}

	if( input.KeyDown( SDL_SCANCODE_UP )
		||
		input.KeyDown( SDL_SCANCODE_DOWN ) )
	{
		m_buttonChangeSound->Play();

		switch( m_currentState )
		{
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
