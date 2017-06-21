#include "CStateMainMenu.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/camera/CCameraOrtho.hpp"

#include "src/engine/states/CStateGame.hpp"

CStateMainMenu::CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
	CState( "main menu", filesystem, settings, engineSystems ),
	m_buttonChangeSound { std::make_shared< CSoundSource>( engineSystems.SoundManager.LoadSoundBuffer( "sounds/Pickup_Coin17.wav" ) ) }
{
	m_buttonChangeSound->SetLooping( false );
	m_buttonChangeSound->SetRelativePositioning( true );

	{
		auto camera = std::make_shared< CCameraOrtho >( m_settings, 0.1f, 1000.0f );
		camera->SetPosition( { 0.0f, 0.0f, 500.0f } );
		camera->SetDirection( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( camera );
	}

	auto &renderer = m_engineSystems.Renderer;
	auto &materialManager = renderer.MaterialManager();
	auto &textureManager = renderer.TextureManager();
	auto &samplerManager = renderer.SamplerManager();

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto material = materialManager.LoadMaterial( "materials/standard.mat" );

		{
			auto bgMeshPrimitive = Primitives::quad;
			bgMeshPrimitive.vertices[ 0 ].x = 0.0f;
			bgMeshPrimitive.vertices[ 0 ].y = 0.0f;
			bgMeshPrimitive.vertices[ 1 ].x = static_cast< float >( windowSize.width );
			bgMeshPrimitive.vertices[ 1 ].y = 0.0f;
			bgMeshPrimitive.vertices[ 2 ].x = 0.0f;
			bgMeshPrimitive.vertices[ 2 ].y = static_cast< float >( windowSize.height );
			bgMeshPrimitive.vertices[ 3 ].x = static_cast< float >( windowSize.width );
			bgMeshPrimitive.vertices[ 3 ].y = static_cast< float >( windowSize.height );

			const CMesh::TTextures bgMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/menu/background.jpg" ), samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

			const auto bgMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, bgMeshPrimitive, material, glm::vec3( 0.0f, 0.0f, 0.0f ), bgMeshTextures );

			m_scene.AddMesh( bgMesh );
		}

		{
			const float halfTitleWidth = windowSize.width * 0.75f / 2;
			const float halfTitleHeight = halfTitleWidth / 4.0f;

			auto titleMeshPrimitive = Primitives::quad;
			titleMeshPrimitive.vertices[ 0 ].x = -halfTitleWidth;
			titleMeshPrimitive.vertices[ 0 ].y = -halfTitleHeight;
			titleMeshPrimitive.vertices[ 1 ].x = halfTitleWidth;
			titleMeshPrimitive.vertices[ 1 ].y = -halfTitleHeight;
			titleMeshPrimitive.vertices[ 2 ].x = -halfTitleWidth;
			titleMeshPrimitive.vertices[ 2 ].y = halfTitleHeight;
			titleMeshPrimitive.vertices[ 3 ].x = halfTitleWidth;
			titleMeshPrimitive.vertices[ 3 ].y = halfTitleHeight;

			const CMesh::TTextures titleMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/menu/title.png" ), samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

			const auto bgTitle = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, titleMeshPrimitive, material, glm::vec3( windowSize.width / 2.0f, windowSize.height - halfTitleHeight, 5.0f ), titleMeshTextures );

			m_scene.AddMesh( bgTitle );
		}
	}

	const float halfButtonWidth = windowSize.width / 4 / 2;
	const float halfButtonHeight = windowSize.height / 6 / 2;

	auto buttonMeshPrimitive = Primitives::quad;
	buttonMeshPrimitive.vertices[ 0 ].x = -halfButtonWidth;
	buttonMeshPrimitive.vertices[ 0 ].y = -halfButtonHeight;
	buttonMeshPrimitive.vertices[ 1 ].x = halfButtonWidth;
	buttonMeshPrimitive.vertices[ 1 ].y = -halfButtonHeight;
	buttonMeshPrimitive.vertices[ 2 ].x = -halfButtonWidth;
	buttonMeshPrimitive.vertices[ 2 ].y = halfButtonHeight;
	buttonMeshPrimitive.vertices[ 3 ].x = halfButtonWidth;
	buttonMeshPrimitive.vertices[ 3 ].y = halfButtonHeight;

	{
		const auto greenMaterial = materialManager.LoadMaterial( "materials/green.mat" );

		m_meshStart = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, buttonMeshPrimitive, greenMaterial, glm::vec3( windowSize.width / 2.0f, 2 * windowSize.height / 4.0f, 10.0f ) );

		m_scene.AddMesh( m_meshStart );
	}

	{
		const auto redMaterial = materialManager.LoadMaterial( "materials/red.mat" );

		m_meshExit = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, buttonMeshPrimitive, redMaterial, glm::vec3( windowSize.width / 2.0f, windowSize.height / 4.0f, 10.0f ) );

		m_scene.AddMesh( m_meshExit );
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
				m_meshStart->SetScale( { 1.0f, 1.0f, 1.0f } );
				m_currentState = eMenuState::EXIT;
				break;
			case eMenuState::EXIT:
				m_meshExit->SetScale( { 1.0f, 1.0f, 1.0f } );
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
				m_meshStart->SetScale( buttonPulseVec3 );
				break;
			case eMenuState::EXIT:
				m_meshExit->SetScale( buttonPulseVec3 );
				break;
		}
	}

	return( shared_from_this() );
}
