#include "CStateMainMenu.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/camera/CCameraOrtho.hpp"

#include "src/engine/states/CStateGame.hpp"

CStateMainMenu::CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
	CState( "main menu", filesystem, settings, engineSystems ),
	m_buttonChangeSound { std::make_shared< CSoundSource>( engineSystems.SoundManager.LoadSoundBuffer( "sounds/Pickup_Coin17.wav" ) ) }
{
	m_buttonChangeSound->SetLooping( false );
	m_buttonChangeSound->SetRelativePositioning( true );

	{
		auto camera = std::make_shared< CCameraOrtho >( "ortho camera", m_settings, 0.1f, 1000.0f );
		camera->Transform.Position( { 0.0f, 0.0f, 500.0f } );
		camera->Direction( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( camera );
	}

	auto &renderer = m_engineSystems.Renderer;
	auto &materialManager = renderer.MaterialManager();
	auto &textureManager = renderer.TextureManager();
	auto &samplerManager = renderer.SamplerManager();

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto material = materialManager.LoadMaterial( "materials/standard.mat" );

		auto bgMeshPrimitive = Primitives::quad;
		bgMeshPrimitive.Vertices[ 0 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 0 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 1 ].Position.x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.Vertices[ 1 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.y = static_cast< float >( windowSize.height );
		bgMeshPrimitive.Vertices[ 3 ].Position.x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.Vertices[ 3 ].Position.y = static_cast< float >( windowSize.height );

		const CMesh::TTextures bgMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/menu/background.jpg" ), samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, bgMeshPrimitive, material, bgMeshTextures );

		std::shared_ptr< CEntity > bg = std::make_shared< CEntity >( "background" );
		bg->Mesh( bgMesh );

		m_scene.AddEntity( bg );
	}

	{
		const auto material = materialManager.LoadMaterial( "materials/standard_blend.mat" );

		const float halfTitleWidth = windowSize.width * 0.75f / 2;
		const float halfTitleHeight = halfTitleWidth / 4.0f;

		auto titleMeshPrimitive = Primitives::quad;
		titleMeshPrimitive.Vertices[ 0 ].Position.x = -halfTitleWidth;
		titleMeshPrimitive.Vertices[ 0 ].Position.y = -halfTitleHeight;
		titleMeshPrimitive.Vertices[ 1 ].Position.x = halfTitleWidth;
		titleMeshPrimitive.Vertices[ 1 ].Position.y = -halfTitleHeight;
		titleMeshPrimitive.Vertices[ 2 ].Position.x = -halfTitleWidth;
		titleMeshPrimitive.Vertices[ 2 ].Position.y = halfTitleHeight;
		titleMeshPrimitive.Vertices[ 3 ].Position.x = halfTitleWidth;
		titleMeshPrimitive.Vertices[ 3 ].Position.y = halfTitleHeight;

		const CMesh::TTextures titleMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/menu/title.png" ), samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgTitleMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, titleMeshPrimitive, material, titleMeshTextures );

		std::shared_ptr< CEntity > bgTitle = std::make_shared< CEntity >( "title" );
		bgTitle->Transform.Position( { windowSize.width / 2.0f, windowSize.height - halfTitleHeight, 5.0f } );
		bgTitle->Mesh( bgTitleMesh );

		m_scene.AddEntity( bgTitle );
	}

	const float halfButtonWidth = windowSize.width / 4 / 2;
	const float halfButtonHeight = windowSize.height / 6 / 2;

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
		const auto greenMaterial = materialManager.LoadMaterial( "materials/green.mat" );

		m_startMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, buttonMeshPrimitive, greenMaterial );

		const auto startEntity = std::make_shared< CEntity >( "start_button" );
		startEntity->Transform.Position( { windowSize.width / 2.0f, 2 * windowSize.height / 4.0f, 10.0f } );
		startEntity->Mesh( m_startMesh );

		m_scene.AddEntity( startEntity );
	}

	{
		const auto redMaterial = materialManager.LoadMaterial( "materials/red.mat" );

		m_exitMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, buttonMeshPrimitive, redMaterial );

		const auto exitEntity = std::make_shared< CEntity >( "exit_button" );
		exitEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height / 4.0f, 10.0f } );
		exitEntity->Mesh( m_exitMesh );

		m_scene.AddEntity( exitEntity );
	}
}

CStateMainMenu::~CStateMainMenu()
{
}

std::shared_ptr<CState> CStateMainMenu::Update(void)
{
	const auto &input = m_engineSystems.Input;

	if( input.KeyDown( SDL_SCANCODE_RETURN ) )
	{
		switch( m_currentState )
		{
			case eMenuState::START:
				return( std::make_shared< CStateGame >( m_filesystem, m_settings, m_engineSystems ) );
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
				m_startMesh->Scale( { 1.0f, 1.0f, 1.0f } );
				m_currentState = eMenuState::EXIT;
				break;
			case eMenuState::EXIT:
				m_exitMesh->Scale( { 1.0f, 1.0f, 1.0f } );
				m_currentState = eMenuState::START;
				break;
		}
	}

	{
		const float max = 1.05f;
		const float min = 1.0f;

		const float halfRange = (max - min) / 2.0f;

		const float buttonPulse = min + halfRange + sin( m_engineSystems.GlobalTimer.Time() / 100000.0f ) * halfRange;

		const glm::vec3 buttonPulseVec3 = { buttonPulse, buttonPulse, buttonPulse };

		switch( m_currentState )
		{
			case eMenuState::START:
				m_startMesh->Scale( buttonPulseVec3 );
				break;
			case eMenuState::EXIT:
				m_exitMesh->Scale( buttonPulseVec3 );
				break;
		}
	}

	return( shared_from_this() );
}
