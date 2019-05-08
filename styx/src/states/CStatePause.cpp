#include "CStatePause.hpp"

#include "src/logger/CLogger.hpp"

#include "src/scene/components/camera/CCameraOrthoComponent.hpp"
#include "src/renderer/components/CModelComponent.hpp"

#include "src/states/CStateMainMenu.hpp"

#include "src/renderer/geometry/prefabs/Quad.hpp"
#include "src/renderer/geometry/prefabs/Rectangle.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface, std::shared_ptr<CState> pausedState ) :
	CState( "pause", filesystem, settings, engineInterface ),
	m_pausedState { pausedState }
{
	m_pausedState->Pause();

	m_scene.ClearColor( CColor( 0.3f, 0.3f, 0.3f, 0.0f ) );

	auto &resources = engineInterface.Resources;

	auto &renderer = engineInterface.Renderer;

	{
		auto cameraEntity = m_scene.CreateEntity( "ortho camera" );
		cameraEntity->Transform.Position( { 0.0f, 0.0f, 500.0f } );
		cameraEntity->Transform.Direction( { 0.0f, 0.0f, -10.0f } );
		cameraEntity->Add<CCameraOrthoComponent>( m_settings.renderer.window.size, 0.1f, 1000.0f );

		m_scene.Camera( cameraEntity );
	}

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto materialPause = resources.Get<CMaterial>( "materials/pause_bg.mat" );

		auto bgGeometry = GeometryPrefabs::QuadPNU0();
		bgGeometry.Vertices[ 0 ].Position.x = 0.0f;
		bgGeometry.Vertices[ 0 ].Position.y = 0.0f;
		bgGeometry.Vertices[ 1 ].Position.x = static_cast<f16>( windowSize.width );
		bgGeometry.Vertices[ 1 ].Position.y = 0.0f;
		bgGeometry.Vertices[ 2 ].Position.x = 0.0f;
		bgGeometry.Vertices[ 2 ].Position.y = static_cast<f16>( windowSize.height );
		bgGeometry.Vertices[ 3 ].Position.x = static_cast<f16>( windowSize.width );
		bgGeometry.Vertices[ 3 ].Position.y = static_cast<f16>( windowSize.height );

		const CMesh::TMeshTextureSlots bgMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( resources.Get<CTexture>( "textures/pause/bg.png" ), renderer.SamplerManager().GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared<CMesh>( bgGeometry, materialPause, bgMeshTextureSlots );

		auto bg = m_scene.CreateEntity( "background" );
		bg->Add<CModelComponent>( bgMesh );
	}

	{
		const f16 pauseElementsWidth = windowSize.width * 0.5f;

		const f16 pauseTextHeight = pauseElementsWidth / 4.0f;
		const f16 screenshotHeight = pauseElementsWidth * ( static_cast<f16>( windowSize.height ) / static_cast<f16>( windowSize.width ) );

		const f16 pauseElementsTotalHeight = pauseTextHeight + screenshotHeight;

		{
			const auto materialPauseText = resources.Get<CMaterial>( "materials/standard_blend.mat" );

			const CMesh::TMeshTextureSlots textMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( resources.Get<CTexture>( "textures/pause/fg.png" ), renderer.SamplerManager().GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };

			const auto meshText = std::make_shared<CMesh>( GeometryPrefabs::RectanglePNU0( pauseElementsWidth, pauseTextHeight ), materialPauseText, textMeshTextureSlots );

			m_textEntity = m_scene.CreateEntity( "text" );
			m_textEntity->Transform.Position( { static_cast<f16>( windowSize.width ) / 2.0f, ( static_cast<f16>( windowSize.height ) / 2.0f ) - ( pauseElementsTotalHeight / 2.0f ) + ( pauseTextHeight / 2.0f ), 5.0f } );
			m_textEntity->Add<CModelComponent>( meshText );
		}

		{
			const auto materialPauseText = resources.Get<CMaterial>( "materials/pause_screenshot.mat" );

			const CMesh::TMeshTextureSlots screenshotMeshTextureSlots = { { "diffuseTexture", std::make_shared<CMeshTextureSlot>( m_pausedState->FrameBuffer().ColorTexture(), renderer.SamplerManager().GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };

			const auto screenshotMesh = std::make_shared<CMesh>( GeometryPrefabs::RectanglePNU0( pauseElementsWidth, screenshotHeight ), materialPauseText, screenshotMeshTextureSlots );

			m_screenshotEntity = m_scene.CreateEntity( "screenshot" );
			m_screenshotEntity->Transform.Position( { static_cast<f16>( windowSize.width ) / 2.0f, ( static_cast<f16>( windowSize.height ) / 2.0f ) - ( pauseElementsTotalHeight / 2.0f ) + pauseTextHeight + ( screenshotHeight / 2.0f ), 5.0f } );
			m_screenshotEntity->Add<CModelComponent>( screenshotMesh );
		}
	}
}

CStatePause::~CStatePause()
{
}

std::shared_ptr<CState> CStatePause::OnUpdate()
{
	const auto yOffset = ( sin( m_timer.Time() / 2000000.0f ) * 0.5f );

	auto posText = m_textEntity->Transform.Position();
	posText.y -= yOffset;
	m_textEntity->Transform.Position( posText );

	auto posScreenshot = m_screenshotEntity->Transform.Position();
	posScreenshot.y -= yOffset;
	m_screenshotEntity->Transform.Position( posScreenshot );

	const auto &input = m_engineInterface.Input;

	if( input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		logINFO( "returning to calling state '{0}'", m_pausedState->Name() );
		m_pausedState->Resume();
		return( m_pausedState );
	}
	else if( input.KeyDown( SDL_SCANCODE_Q ) )
	{
		logINFO( "ESC pressed, ending game..." );
		return( std::make_shared<CStateMainMenu>( m_filesystem, m_settings, m_engineInterface ) );
	}

	return( shared_from_this() );
}
