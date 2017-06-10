#include "CStateGame.hpp"

#include <algorithm>


#include "src/engine/math/Math.hpp"
#include "src/engine/helper/Date.hpp"
#include "src/engine/helper/geom/Primitives.hpp"
#include "src/engine/helper/image/ImageHandler.hpp"

#include "src/engine/logger/CLogger.hpp"

CStateGame::CStateGame( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems ) :
	CState( "game", filesystem, settings, engineSystems )
{
	auto &renderer = m_engineSystems.Renderer;

	renderer.SetClearColor( CColor( 0.0f, 0.0f, 4.0f, 0.0f ) );

	m_cameraFree = std::make_shared< CCameraFree >( m_settings.renderer.window.aspect_ratio, 72.0f, 0.1f, 1000.0f );
	m_cameraFree->SetPosition( { 0.0f, 10.0f, 10.0f } );
	m_cameraFree->SetDirection( { 0.0f, 0.0f, -10.0f } );

	m_scene.Camera( m_cameraFree );

	auto &soundManager = m_engineSystems.SoundManager;

	soundManager.SetListener( m_cameraFree->Position(), m_cameraFree->Direction(), m_cameraFree->Up() );

	auto &materialManager = renderer.MaterialManager();
	auto &textureManager = renderer.TextureManager();
	auto &samplerManager = renderer.SamplerManager();

	// create floor
	{
		const auto material = materialManager.LoadMaterial( "materials/standard.mat" );

		auto floorMeshPrimitive = Primitives::quad;

		for( auto &coord : floorMeshPrimitive.texcoords )
		{
			coord *= 10;
		}

		const CMesh::TTextures floorMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/texpack_2/stone_floor.png" ), samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D ) ) } };

		const auto floorMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, floorMeshPrimitive, material, glm::vec3( 0.0f, 0.0f, 0.0f ), floorMeshTextures );
		floorMesh->SetScale( { 100.0f, 100.0f, 100.0f } );
		floorMesh->SetOrientation( { -90.0f, 00.0f, 0.0f } );

		m_scene.AddMesh( floorMesh );
	}

	//auto material2 = materialManager.LoadMaterial( "materials/flames.mat" );
	//auto material2 = materialManager.LoadMaterial( "materials/texture_from_zip.mat" );
	//auto material2 = materialManager.LoadMaterial( "materials/newscast.mat" );
	//auto material2 = materialManager.LoadMaterial( "textures/texpack_1/killblockgeomtrn.png" );

	{
		const auto materialWaitCursor = materialManager.LoadMaterial( "materials/wait_cursor.mat" );

		const CMesh::TTextures movableMeshTextures = {	{ "skullTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/cursor/skull.png" ), samplerManager.SamplerFromType( CSampler::Type::EDGE_2D ) ) },
														{ "waitTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/cursor/wait.png" ), samplerManager.SamplerFromType( CSampler::Type::EDGE_2D ) ) } };

		m_movableMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialWaitCursor, glm::vec3( 0.0f, 10.0f, 20.0f ), movableMeshTextures );
		m_movableMesh->SetScale( { 3.0f, 3.0f, 1.0f } );

		m_scene.AddMesh( m_movableMesh );
	}

	// create small cube of cubes
	{
		const auto material1 = materialManager.LoadMaterial( "materials/schnarf.mat" );

		const CMesh::TTextures schnarfMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/texpack_1/window_buildingside_06.jpg" ), samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D ) ) } };

		const std::uint16_t cubeSize { 4 };

		for( std::uint16_t i = 0; i < cubeSize; i++ )
		{
			for( std::uint16_t j = 0; j < cubeSize; j++ )
			{
				for( std::uint16_t k = 0; k < cubeSize; k++ )
				{
					const auto mesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material1, glm::vec3( 20.0f + i * 4.0f, ( 0.0f + j * 4.0f ) + 2, -10.0f + k * 4.0f ), schnarfMeshTextures );
					mesh->SetScale( { 2.0f, 2.0f, 2.0f } );

					m_scene.AddMesh( mesh );
				}
			}
		}
	}

	{
		const auto materialSuperBox = materialManager.LoadMaterial( "materials/superBox.mat" );

		const CMesh::TTextures superBoxMeshTextures = {	{ "bgTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/texpack_1/mybitmap.bmp" ), samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D ) ) },
														{ "fgTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/texpack_1/senn_icyfangrate.tga" ), samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D ) ) },
														{ "skyBoxTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/cube/sixtine/sixtine.cub" ), samplerManager.SamplerFromType( CSampler::Type::EDGE_CUBE ) ) } };

		{
			const auto m_mesh2 = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, materialSuperBox, glm::vec3( 0.0f, 10.0f, -10.0f ), superBoxMeshTextures );
			m_mesh2->SetScale( { 10.0f, 10.0f, 10.0f } );

			m_scene.AddMesh( m_mesh2 );
		}

		// create big cube of cubes
		{
			const std::uint16_t cubeSize { 14 };

			for( std::uint16_t i = 0; i < cubeSize; i++ )
			{
				for( std::uint16_t j = 0; j < cubeSize; j++ )
				{
					for( std::uint16_t k = 0; k < cubeSize; k++ )
					{
						const auto mesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, materialSuperBox, glm::vec3( 20.0f + i * 4.0f, ( 0.0f + j * 4.0f ) + 2, 50.0f + k * 4.0f ), superBoxMeshTextures );
						mesh->SetScale( { 2.0f, 2.0f, 2.0f } );

						m_scene.AddMesh( mesh );
					}
				}
			}
		}
	}

	// create big cube of cubes
	{
		const auto material = materialManager.LoadMaterial( "materials/standard.mat" );

		const CMesh::TTextures meshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/texpack_1/black_border.png" ), samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D ) ) } };

		const std::uint16_t cubeSize { 10  };

		for( std::uint16_t i = 0; i < cubeSize; i++ )
		{
			for( std::uint16_t j = 0; j < cubeSize; j++ )
			{
				for( std::uint16_t k = 0; k < cubeSize; k++ )
				{
					if( Math::irand( 0, 1 ) == 1 )
					{
						const auto mesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material, glm::vec3( -40.0f + i * 4.0f, ( 0.0f + j * 4.0f ) + 2, 50.0f + k * 4.0f ), meshTextures );
						mesh->SetScale( { 2.0f, 2.0f, 2.0f } );

						m_scene.AddMesh( mesh );
					}
				}
			}
		}
	}

	{
		const auto fireMaterial = materialManager.LoadMaterial( "materials/flames.mat" );

		const CMesh::TTextures flamesMeshTextures = { { "diffuseTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/array/fire/fire.arr" ), samplerManager.SamplerFromType( CSampler::Type::EDGE_2D ) ) } };

		const auto mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, fireMaterial, glm::vec3( -5.0f, 10.0f, 1.0f ), flamesMeshTextures );
		mesh->SetScale( { 4.0f, 8.0f, 1.0f } );

		m_scene.AddMesh( mesh );
	}

	{
		const auto greenMaterial = materialManager.LoadMaterial( "materials/green.mat" );

		const auto mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, greenMaterial, glm::vec3( -4.0f, 10.0f, 1.0f ) );
		mesh->SetScale( { 2.0f, 2.0f, 1.0f } );

		m_scene.AddMesh( mesh );
	}

	{
		const auto pulseMaterial = materialManager.LoadMaterial( "materials/pulse_green_red.mat" );

		m_pulseMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, pulseMaterial, glm::vec3( 0.0f, 10.0f, 1.0f ) );
		m_pulseMesh->SetScale( { 2.0f, 2.0f, 1.0f } );

		m_scene.AddMesh( m_pulseMesh );
	}

	{
		const auto redMaterial = materialManager.LoadMaterial( "materials/red.mat" );

		const auto mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, redMaterial, glm::vec3( 4.0f, 10.0f, 1.0f ) );
		mesh->SetScale( { 2.0f, 2.0f, 1.0f } );

		m_scene.AddMesh( mesh );
	}

	{
		const auto material3 = materialManager.LoadMaterial( "materials/sky.mat" );

		const CMesh::TTextures skyMeshTextures = { { "skyboxTexture", std::make_shared< CMeshTexture >( textureManager.LoadTexture( "textures/cube/sixtine/sixtine.cub" ), samplerManager.SamplerFromType( CSampler::Type::EDGE_CUBE ) ) } };

		m_skyboxMesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material3, skyMeshTextures );

		m_scene.AddMesh( m_skyboxMesh );
	}

	m_backgroundMusic = std::make_shared< CSoundSource >( soundManager.LoadSoundBuffer( "music/rise_of_spirit.ogg" ) );
	m_backgroundMusic->Play();
	m_backgroundMusic->SetLooping( true );
}

CStateGame::~CStateGame()
{
}

std::shared_ptr< CState > CStateGame::Update( void )
{
	auto &renderer = m_engineSystems.Renderer;

	auto &soundManager = m_engineSystems.SoundManager;

	const auto &input = m_engineSystems.Input;

	if( input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		logINFO( "pause" );
		return( std::make_shared< CStatePause >( m_filesystem, m_settings, m_engineSystems, shared_from_this() ) );
	}

	const float spp = 2.0f * m_settings.engine.tick / 1000000;

	// TODO 1: create a way to reload all resources with one function
	// TODO 2: maybe create a way for systems to hook into the inputsystem, so we can provide globally active keyboard-shortcuts?
	if( input.KeyDown( SDL_SCANCODE_F8 ) )
	{
		renderer.ReloadResources();
	}

	/*
	 * move pulseMesh
	 */
	{
		auto pos = m_pulseMesh->Position();
		pos.y = 10.0f + ( sin( m_engineSystems.GlobalTimer.Time() / 2000000.0f ) * 5.0f );
		m_pulseMesh->SetPosition( pos );
	}

	/*
	 * move meshMovable
	 */

	if( input.KeyStillDown( SDL_SCANCODE_KP_6 ) )
	{
		glm::vec3 pos = m_movableMesh->Position();
		pos.x += spp;
		m_movableMesh->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_4 ) )
	{
		glm::vec3 pos = m_movableMesh->Position();
		pos.x -= spp;
		m_movableMesh->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_8 ) )
	{
		glm::vec3 pos = m_movableMesh->Position();
		pos.y += spp;
		m_movableMesh->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_2 ) )
	{
		glm::vec3 pos = m_movableMesh->Position();
		pos.y -= spp;
		m_movableMesh->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_PLUS ) )
	{
		glm::vec3 pos = m_movableMesh->Position();
		pos.z += spp;
		m_movableMesh->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_MINUS ) )
	{
		glm::vec3 pos = m_movableMesh->Position();
		pos.z -= spp;
		m_movableMesh->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_5 ) )
	{
		m_movableMesh->SetPosition( glm::vec3() );
	}

	/*
	 * move camera
	 */

	const float ctrlPressedMult = input.KeyStillDown( SDL_SCANCODE_LCTRL ) ? 1 : 10;

	if( input.MouseStillDown( SDL_BUTTON_LEFT) )
	{
		m_cameraFree->Rotate( input.MouseDeltaY(), input.MouseDeltaX() );
	}

	if( input.KeyDown( SDL_SCANCODE_A )
        ||
		input.KeyStillDown( SDL_SCANCODE_A ) )
	{
		m_cameraFree->MoveLeft( spp * ctrlPressedMult );
	}

	if( input.KeyDown( SDL_SCANCODE_D )
        ||
		input.KeyStillDown( SDL_SCANCODE_D ) )
	{
		m_cameraFree->MoveRight( spp * ctrlPressedMult );
	}

	if( input.KeyDown( SDL_SCANCODE_W )
        ||
		input.KeyStillDown( SDL_SCANCODE_W ) )
	{
		m_cameraFree->MoveForward( spp * ctrlPressedMult );
	}

	if( input.KeyDown( SDL_SCANCODE_S )
        ||
		input.KeyStillDown( SDL_SCANCODE_S ) )
	{
		m_cameraFree->MoveBackward( spp * ctrlPressedMult );
	}

	if( input.KeyDown( SDL_SCANCODE_SPACE )
        ||
		input.KeyStillDown( SDL_SCANCODE_SPACE ) )
	{
		m_cameraFree->MoveUp( spp * ctrlPressedMult );
	}

	if( input.KeyDown( SDL_SCANCODE_LSHIFT )
        ||
		input.KeyStillDown( SDL_SCANCODE_LSHIFT ) )
	{
		m_cameraFree->MoveDown( spp * ctrlPressedMult );
	}

	soundManager.SetListener( m_cameraFree->Position(), m_cameraFree->Direction(), m_cameraFree->Up() );

	/*
	 * change FOV
	 */
	if( input.KeyStillDown( SDL_SCANCODE_PAGEUP ) )
	{
		auto fov = m_cameraFree->FOV();
		fov++;
		m_cameraFree->SetFOV( fov );
		logDEBUG( "new FOV: {0}", fov );

	}
	if( input.KeyStillDown( SDL_SCANCODE_PAGEDOWN ) )
	{
		auto fov = m_cameraFree->FOV();
		fov--;
		m_cameraFree->SetFOV( fov );
		logDEBUG( "new FOV: {0}", fov );
	}

	/*
	 * screenshot
	 */

	if( input.KeyDown( SDL_SCANCODE_BACKSPACE ) )
	{
		const std::string screenshotDir { "screenshots" };

		if( !m_filesystem.Exists( screenshotDir ) )
		{
			if( !m_filesystem.MakeDir( screenshotDir ) )
			{
				logERROR( "couldn't create screenshot-directory '{0}' because of: {1}", screenshotDir, m_filesystem.GetLastError() );
			}
		}

		std::string datetime = Date::GetCurrentDateTimeString();
		std::replace( std::begin( datetime ), std::end( datetime ), ':', '.' );

		const std::string screenshotPath = screenshotDir + CFileSystem::GetDirSeparator() + datetime + "." + m_settings.renderer.screenshot.format;

		logINFO( "taking screenshot '{0}'", screenshotPath );

		const std::shared_ptr< const CImage > screenshot = renderer.GetScreenshot();

		if( !ImageHandler::Save( m_filesystem, screenshot, m_settings.renderer.screenshot.scale_factor, m_settings.renderer.screenshot.format, screenshotPath ) )
		{
			logERROR( "screenshot '{0}' couldn't be saved", screenshotPath );
		}
		else
		{
			if( !m_filesystem.Exists( screenshotPath ) )
			{
				logERROR( "screenshot '{0}' doesn't exist", screenshotPath );
			}
		}
	}

	/*
	 * stuff
	 */

	if( !input.MouseStillDown( SDL_BUTTON_LEFT) )
	{
		m_movableMesh->SetOrientation( glm::vec3( m_yrot / 2, m_xrot / 2, 0.0f ) );
	}

	m_rotx_ps = input.MouseDeltaX();
	m_roty_ps = input.MouseDeltaY();

	m_xrot += m_rotx_ps;
	m_yrot += m_roty_ps;

	// m_cameraFree->SetDirection( mesh->Position() - m_cameraFree->Position() );

	m_skyboxMesh->SetPosition( m_cameraFree->Position() );

	return( shared_from_this() );
}
