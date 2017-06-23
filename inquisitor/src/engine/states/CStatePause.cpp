#include "CStatePause.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/camera/CCameraOrtho.hpp"

#include "src/engine/states/CStateMainMenu.hpp"

CStatePause::CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems, std::shared_ptr< CState > pausedState ) :
	CState( "pause", filesystem, settings, engineSystems ),
	m_startTime { engineSystems.GlobalTimer.Time() },
	m_pausedState { pausedState }
{
	m_scene.ClearColor( CColor( 0.3f, 0.3f, 0.3f, 0.0f ) );

	auto &renderer = engineSystems.Renderer;

	{
		auto camera = std::make_shared< CCameraOrtho >( m_settings, 0.1f, 1000.0f );
		camera->SetPosition( { 0.0f, 0.0f, 500.0f } );
		camera->SetDirection( { 0.0f, 0.0f, -10.0f } );

		m_scene.Camera( camera );
	}

	const CSize &windowSize = settings.renderer.window.size;

	{
		const auto materialPause = renderer.MaterialManager().LoadMaterial( "materials/pause_bg.mat" );

		auto bgMeshPrimitive = Primitives::quad;
		bgMeshPrimitive.vertices[ 0 ].x = 0.0f;
		bgMeshPrimitive.vertices[ 0 ].y = 0.0f;
		bgMeshPrimitive.vertices[ 1 ].x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.vertices[ 1 ].y = 0.0f;
		bgMeshPrimitive.vertices[ 2 ].x = 0.0f;
		bgMeshPrimitive.vertices[ 2 ].y = static_cast< float >( windowSize.height );
		bgMeshPrimitive.vertices[ 3 ].x = static_cast< float >( windowSize.width );
		bgMeshPrimitive.vertices[ 3 ].y = static_cast< float >( windowSize.height );

		const CMesh::TTextures bgMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/pause/bg.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D ) ) } };

		const auto bgMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, bgMeshPrimitive, materialPause, glm::vec3( 0.0f, 0.0f, 0.0f ), bgMeshTextures );

		m_scene.AddMesh( bgMesh );
	}

	{
		const auto materialPauseText = renderer.MaterialManager().LoadMaterial( "materials/standard_blend.mat" );

		const float halfPauseElementsWidth = windowSize.width * 0.5f / 2;

		const float halfPauseTextHeight = halfPauseElementsWidth / 4.0f;
		const float halfScreenshotHeight = ( halfPauseElementsWidth / windowSize.width ) * windowSize.height;

		{
			auto pauseTextMeshPrimitive = Primitives::quad;
			pauseTextMeshPrimitive.vertices[ 0 ].x = -halfPauseElementsWidth;
			pauseTextMeshPrimitive.vertices[ 0 ].y = -halfPauseTextHeight;
			pauseTextMeshPrimitive.vertices[ 1 ].x = halfPauseElementsWidth;
			pauseTextMeshPrimitive.vertices[ 1 ].y = -halfPauseTextHeight;
			pauseTextMeshPrimitive.vertices[ 2 ].x = -halfPauseElementsWidth;
			pauseTextMeshPrimitive.vertices[ 2 ].y = halfPauseTextHeight;
			pauseTextMeshPrimitive.vertices[ 3 ].x = halfPauseElementsWidth;
			pauseTextMeshPrimitive.vertices[ 3 ].y = halfPauseTextHeight;

			const CMesh::TTextures textMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( renderer.TextureManager().LoadTexture( "textures/pause/fg.png" ), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::EDGE_2D ) ) } };

			m_meshText = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, pauseTextMeshPrimitive, materialPauseText, glm::vec3( windowSize.width / 2.0f, windowSize.height - ( 2 * halfPauseTextHeight ) - ( 2 * halfScreenshotHeight ), 5.0f ), textMeshTextures );

			m_scene.AddMesh( m_meshText );
		}

		{
			auto screenshotMeshPrimitive = Primitives::quad;
			screenshotMeshPrimitive.vertices[ 0 ].x = -halfPauseElementsWidth;
			screenshotMeshPrimitive.vertices[ 0 ].y = -halfScreenshotHeight;
			screenshotMeshPrimitive.vertices[ 1 ].x = halfPauseElementsWidth;
			screenshotMeshPrimitive.vertices[ 1 ].y = -halfScreenshotHeight;
			screenshotMeshPrimitive.vertices[ 2 ].x = -halfPauseElementsWidth;
			screenshotMeshPrimitive.vertices[ 2 ].y = halfScreenshotHeight;
			screenshotMeshPrimitive.vertices[ 3 ].x = halfPauseElementsWidth;
			screenshotMeshPrimitive.vertices[ 3 ].y = halfScreenshotHeight;

			const CMesh::TTextures screenshotMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( m_pausedState->FrameBuffer().ColorTexture(), renderer.SamplerManager().SamplerFromSamplerType( CSampler::SamplerType::EDGE_2D ) ) } };

			m_screenshotMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, screenshotMeshPrimitive, materialPauseText, glm::vec3( windowSize.width / 2.0f, windowSize.height - halfPauseTextHeight - halfScreenshotHeight, 5.0f ), screenshotMeshTextures );

			m_scene.AddMesh( m_screenshotMesh );
		}
	}
}

CStatePause::~CStatePause()
{
}

std::shared_ptr< CState > CStatePause::Update( void )
{
	const auto yOffset = ( sin( m_engineSystems.GlobalTimer.Time() / 2000000.0 ) * 0.5f );

	auto posText = m_meshText->Position();
	posText.y -= yOffset;
	m_meshText->SetPosition( posText );

	auto posScreenshot = m_screenshotMesh->Position();
	posScreenshot.y -= yOffset;
	m_screenshotMesh->SetPosition( posScreenshot );

	const auto &input = m_engineSystems.Input;

	if( input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		logINFO( "returning to calling state '{0}'", m_pausedState->Name() );
		return( m_pausedState );
	}
	else if( input.KeyDown( SDL_SCANCODE_Q ) )
	{
		logINFO( "ESC pressed, ending game..." );
		return( std::make_shared< CStateMainMenu >( m_filesystem, m_settings, m_engineSystems ) );
	}

	return( shared_from_this() );
}
