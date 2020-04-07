#include "CStateMainMenu.hpp"

#include "src/system/CEngine.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/components/CGuiModelComponent.hpp"

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

	auto &resources = m_engineInterface.Resources;
	auto &samplerManager = m_engineInterface.SamplerManager;
	auto &fontbuilder = m_engineInterface.FontBuilder;

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto material = resources.Get<CMaterial>( "materials/standard.mat" );

		auto bgGeometry = GeometryPrefabs::RectanglePU0( windowSize.width, windowSize.height );

		const CMesh::TMeshTextureSlots bgMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( resources.Get<CTexture>( "textures/menu/background.jpg" ), samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared<CMesh>( bgGeometry, material, bgMeshTextureSlots );

		auto bg = m_scene.CreateEntity( "background" );
		bg->Transform.Position = { windowSize.width / 2.0f, windowSize.height / 2.0f, -10.0f };
		bg->Add<CGuiModelComponent>( bgMesh );
	}

	{
		const auto material = resources.Get<CMaterial>( "materials/standard_blend.mat" );

		const f16 titleWidth = windowSize.width * 0.75f;
		const f16 titleHeight = titleWidth / 4.0f;

		auto titleGeometry = GeometryPrefabs::RectanglePNU0( titleWidth, titleHeight );

		const CMesh::TMeshTextureSlots titleMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( resources.Get<CTexture>( "textures/menu/title.png" ), samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgTitleMesh = std::make_shared<CMesh>( titleGeometry, material, titleMeshTextureSlots );

		auto bgTitle = m_scene.CreateEntity( "title" );
		bgTitle->Transform.Position = { windowSize.width / 2.0f, windowSize.height - ( titleHeight / 2.0f ), -5.0f };
		bgTitle->Add<CGuiModelComponent>( bgTitleMesh );
	}

	const f16 buttonWidth = windowSize.width / 4.0f;
	const f16 buttonHeight = windowSize.height / 6.0f;

	auto buttonGeometry = GeometryPrefabs::RectangleP( buttonWidth, buttonHeight );

	{
		const auto greenMaterial = resources.Get<CMaterial>( "materials/green.mat" );

		const auto startMesh = std::make_shared<CMesh>( buttonGeometry, greenMaterial );

		m_startEntity = m_scene.CreateEntity( "start_button" );
		m_startEntity->Transform.Position = { windowSize.width / 2.0f, 2 * windowSize.height / 4.0f, -5.0f };
		m_startEntity->Add<CGuiModelComponent>( startMesh );
	}

	{
		const auto redMaterial = resources.Get<CMaterial>( "materials/red.mat" );

		const auto exitMesh = std::make_shared<CMesh>( buttonGeometry, redMaterial );

		m_exitEntity = m_scene.CreateEntity( "exit_button" );
		m_exitEntity->Transform.Position = { windowSize.width / 2.0f, windowSize.height / 4.0f, -5.0f };
		m_exitEntity->Add<CGuiModelComponent>( exitMesh );
	}

	{
		const auto fontSize = windowSize.height / 40;

		const auto font = fontbuilder.FromFile( "Comfortaa", "fonts/Comfortaa/Regular.ttf", "fonts/Comfortaa/Bold.ttf", fontSize, CGlyphRange::Default() );

		STextOptions textOptions;
		textOptions.Color = TangoColors::Aluminium();
		textOptions.HorizontalAnchor = EHorizontalAnchor::CENTER;
		textOptions.VerticalAnchor = EVerticalAnchor::CENTER;
		textOptions.HorizontalAlign = EHorizontalAlign::CENTER;

		const auto text = engineInterface.TextBuilder.Create( font, textOptions, "<#{0}><b>{1}</b></#>\ndeveloped by Markus Lobedann", TangoColors::AluminiumHighlight().rgbHex(), CEngine::GetVersionString() );

		const auto entity = m_scene.CreateEntity( "text" );
		entity->Transform.Position = { windowSize.width / 2.0f, 2 * fontSize, 0.0f };
		entity->Add<CGuiModelComponent>( text->Mesh() );
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
				m_startEntity->Transform.Scale = { 1.0f, 1.0f, 1.0f };
				m_exitEntity->Transform.Scale = { 1.0f, 1.0f, 1.0f };
				break;
			case eMenuState::START:
				m_startEntity->Transform.Scale = { 1.0f, 1.0f, 1.0f };
				m_currentState = eMenuState::EXIT;
				break;
			case eMenuState::EXIT:
				m_exitEntity->Transform.Scale = { 1.0f, 1.0f, 1.0f };
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
				m_startEntity->Transform.Scale = buttonPulseVec3;
				break;
			case eMenuState::EXIT:
				m_exitEntity->Transform.Scale = buttonPulseVec3;
				break;
		}
	}

	return( shared_from_this() );
}
