#include "CStatePause.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/camera/CCameraOrtho.hpp"

#include "src/engine/states/CStateMainMenu.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface, std::shared_ptr< CState > pausedState ) :
	CState( "pause", filesystem, settings, engineInterface ),
	m_startTime { engineInterface.GlobalTimer.Time() },
	m_pausedState { pausedState }
{
	m_scene.ClearColor( CColor( 0.3f, 0.3f, 0.3f, 0.0f ) );

	auto &renderer = engineInterface.Renderer;

	{
		auto camera = std::make_shared< CCameraOrtho >( "ortho camera", m_settings, 0.1f, 1000.0f );
		camera->Transform.Position( { 0.0f, 0.0f, 500.0f } );
		camera->Direction( { 0.0f, 0.0f, -10.0f } );

		m_scene.AddEntity( camera );
		m_scene.Camera( camera );
	}

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto materialPause = renderer.MaterialManager().LoadMaterial( "materials/pause_bg.mat" );

		auto bgMeshPrimitive = Primitives::quad;
		bgMeshPrimitive.Vertices[ 0 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 0 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 1 ].Position.x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.Vertices[ 1 ].Position.y = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.x = 0.0f;
		bgMeshPrimitive.Vertices[ 2 ].Position.y = static_cast< float >( windowSize.height );
		bgMeshPrimitive.Vertices[ 3 ].Position.x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.Vertices[ 3 ].Position.y = static_cast< float >( windowSize.height );

		const CMesh::TTextures bgMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/pause/bg.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, bgMeshPrimitive, materialPause, bgMeshTextures );

		std::shared_ptr< CEntity > bg = std::make_shared< CEntity >( "background" );
		bg->Mesh( bgMesh );

		m_scene.AddEntity( bg );
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

			const auto materialPauseText = renderer.MaterialManager().LoadMaterial( "materials/standard_blend.mat" );

			const CMesh::TTextures textMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/pause/fg.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::EDGE_2D ) ) } };

			const auto meshText = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, pauseTextMeshPrimitive, materialPauseText, textMeshTextures );

			m_textEntity = std::make_shared< CEntity >( "text" );
			m_textEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height - ( 2 * halfPauseTextHeight ) - ( 2 * halfScreenshotHeight ), 5.0f } );
			m_textEntity->Mesh( meshText );

			m_scene.AddEntity( m_textEntity );
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

			const auto materialPauseText = renderer.MaterialManager().LoadMaterial( "materials/pause_screenshot.mat" );

			const CMesh::TTextures screenshotMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( m_pausedState->FrameBuffer().ColorTexture(), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::EDGE_2D ) ) } };

			const auto screenshotMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, screenshotMeshPrimitive, materialPauseText, screenshotMeshTextures );

			m_screenshotEntity = std::make_shared< CEntity >( "screenshot" );
			m_screenshotEntity->Transform.Position( { windowSize.width / 2.0f, windowSize.height - halfPauseTextHeight - halfScreenshotHeight, 5.0f } );
			m_screenshotEntity->Mesh( screenshotMesh );

			m_scene.AddEntity( m_screenshotEntity );
		}
	}
}

CStatePause::~CStatePause()
{
}

std::shared_ptr< CState > CStatePause::Update( void )
{
	const auto yOffset = ( sin( m_engineInterface.GlobalTimer.Time() / 2000000.0 ) * 0.5f );

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
		return( m_pausedState );
	}
	else if( input.KeyDown( SDL_SCANCODE_Q ) )
	{
		logINFO( "ESC pressed, ending game..." );
		return( std::make_shared< CStateMainMenu >( m_filesystem, m_settings, m_engineInterface ) );
	}

	return( shared_from_this() );
}
