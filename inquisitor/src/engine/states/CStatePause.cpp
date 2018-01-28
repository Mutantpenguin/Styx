#include "CStatePause.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/components/camera/CCameraOrthoComponent.hpp"

#include "src/engine/states/CStateMainMenu.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface, std::shared_ptr< CState > pausedState ) :
	CState( "pause", filesystem, settings, engineInterface ),
	m_startTime { m_timer.Time() },
	m_pausedState { pausedState }
{
	m_pausedState->Pause();

	m_scene.ClearColor( CColor( 0.3f, 0.3f, 0.3f, 0.0f ) );

	auto &resourceCache = engineInterface.ResourceCacheManager;

	auto &renderer = engineInterface.Renderer;

	{
		auto cameraEntity = m_scene.CreateEntity( "ortho camera" );
		cameraEntity->Transform.Position( { 0.0f, 0.0f, 500.0f } );
		auto camera = cameraEntity->Add< CCameraOrthoComponent >( m_settings.renderer.window.size, 0.1f, 1000.0f );
		camera->Direction( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( cameraEntity );
	}

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto materialPause = resourceCache.GetResource< CMaterial >( "materials/pause_bg.mat" );

		auto bgMeshPrimitive = Primitives::quad;
		bgMeshPrimitive.Vertices[ 0 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 0 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 1 ].Position.x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.Vertices[ 1 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.y = static_cast< float >( windowSize.height );
		bgMeshPrimitive.Vertices[ 3 ].Position.x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.Vertices[ 3 ].Position.y = static_cast< float >( windowSize.height );

		const CMesh::TMeshTextureSlots bgMeshTextureSlots = { { "diffuseTexture", std::make_shared< CMeshTextureSlot >( resourceCache.GetResource< CTexture >( "textures/pause/bg.png" ), renderer.SamplerManager().GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, bgMeshPrimitive, materialPause, bgMeshTextureSlots );

		auto bg = m_scene.CreateEntity( "background" );
		bg->Mesh( bgMesh );
	}

	{
		const float halfPauseElementsWidth = windowSize.width * 0.5f / 2;

		const float halfPauseTextHeight = halfPauseElementsWidth / 4.0f;
		const float halfScreenshotHeight = ( halfPauseElementsWidth / windowSize.width ) * windowSize.height;

		{
			auto pauseTextMeshPrimitive = Primitives::quad;
			pauseTextMeshPrimitive.Vertices[ 0 ].Position.x = -halfPauseElementsWidth;
			pauseTextMeshPrimitive.Vertices[ 0 ].Position.y = -halfPauseTextHeight;
			pauseTextMeshPrimitive.Vertices[ 1 ].Position.x = halfPauseElementsWidth;
			pauseTextMeshPrimitive.Vertices[ 1 ].Position.y = -halfPauseTextHeight;
			pauseTextMeshPrimitive.Vertices[ 2 ].Position.x = -halfPauseElementsWidth;
			pauseTextMeshPrimitive.Vertices[ 2 ].Position.y = halfPauseTextHeight;
			pauseTextMeshPrimitive.Vertices[ 3 ].Position.x = halfPauseElementsWidth;
			pauseTextMeshPrimitive.Vertices[ 3 ].Position.y = halfPauseTextHeight;

			const auto materialPauseText = resourceCache.GetResource< CMaterial >( "materials/standard_blend.mat" );

			const CMesh::TMeshTextureSlots textMeshTextureSlots = { { "diffuseTexture", std::make_shared< CMeshTextureSlot >( resourceCache.GetResource< CTexture >( "textures/pause/fg.png" ), renderer.SamplerManager().GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };

			const auto meshText = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, pauseTextMeshPrimitive, materialPauseText, textMeshTextureSlots );

			m_textEntity = m_scene.CreateEntity( "text" );
			m_textEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height - ( 2 * halfPauseTextHeight ) - ( 2 * halfScreenshotHeight ), 5.0f } );
			m_textEntity->Mesh( meshText );
		}

		{
			auto screenshotMeshPrimitive = Primitives::quad;
			screenshotMeshPrimitive.Vertices[ 0 ].Position.x = -halfPauseElementsWidth;
			screenshotMeshPrimitive.Vertices[ 0 ].Position.y = -halfScreenshotHeight;
			screenshotMeshPrimitive.Vertices[ 1 ].Position.x = halfPauseElementsWidth;
			screenshotMeshPrimitive.Vertices[ 1 ].Position.y = -halfScreenshotHeight;
			screenshotMeshPrimitive.Vertices[ 2 ].Position.x = -halfPauseElementsWidth;
			screenshotMeshPrimitive.Vertices[ 2 ].Position.y = halfScreenshotHeight;
			screenshotMeshPrimitive.Vertices[ 3 ].Position.x = halfPauseElementsWidth;
			screenshotMeshPrimitive.Vertices[ 3 ].Position.y = halfScreenshotHeight;

			const auto materialPauseText = resourceCache.GetResource< CMaterial >( "materials/pause_screenshot.mat" );

			const CMesh::TMeshTextureSlots screenshotMeshTextureSlots = { { "diffuseTexture", std::make_shared< CMeshTextureSlot >( m_pausedState->FrameBuffer().ColorTexture(), renderer.SamplerManager().GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };

			const auto screenshotMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, screenshotMeshPrimitive, materialPauseText, screenshotMeshTextureSlots );

			m_screenshotEntity = m_scene.CreateEntity( "screenshot" );
			m_screenshotEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height - halfPauseTextHeight - halfScreenshotHeight, 5.0f } );
			m_screenshotEntity->Mesh( screenshotMesh );
		}
	}
}

CStatePause::~CStatePause()
{
}

std::shared_ptr< CState > CStatePause::OnUpdate( void )
{
	const auto yOffset = ( sin( m_timer.Time() / 2000000.0 ) * 0.5f );

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
		return( std::make_shared< CStateMainMenu >( m_filesystem, m_settings, m_engineInterface ) );
	}

	return( shared_from_this() );
}
