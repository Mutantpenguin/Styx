#include "CStateGame.hpp"

#include <algorithm>

#include "src/engine/helper/Date.hpp"
#include "src/engine/helper/geom/Primitives.hpp"
#include "src/engine/helper/image/ImageHandler.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/sound/CSound.hpp"

CStateGame::CStateGame( const CFileSystem &filesystem, const CSettings &settings, CSoundManager &soundManager, CRenderer &renderer ) :
	CState( "game", filesystem, settings )
{
	renderer.SetClearColor( CColor( 0.0f, 0.0f, 4.0f, 0.0f ) );

	m_cameraFree = std::make_shared< CCameraFree >( m_settings.renderer.window.aspect_ratio, 90.0f, 0.1f, 1000.0f );
	// TODO when the FOV is not 90, strange things happen
	//m_cameraFree = std::make_shared< CCameraFree >( m_settings.renderer.window.aspect_ratio, 91.0f, 0.1f, 1000.0f );
	m_cameraFree->SetPosition( { 0.0f, 10.0f, 10.0f } );
	m_cameraFree->SetDirection( { 0.0f, 0.0f, -10.0f } );

	m_scene.Camera( m_cameraFree );

	soundManager.SetListener( m_cameraFree );

	// create floor
	{
		const auto material = renderer.LoadMaterial( "materials/floor.mat" );

		auto floorMeshPrimitive = Primitives::quad;

		for( auto &coord : floorMeshPrimitive.texcoords )
		{
			coord *= 10;
		}

		const auto floorMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, floorMeshPrimitive, material, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		floorMesh->SetScale( { 100.0f, 100.0f, 100.0f } );
		floorMesh->SetOrientation( { -90.0f, 00.0f, 0.0f } );

		m_scene.AddMesh( floorMesh );
	}

	//auto material2 = renderer.LoadMaterial( "materials/flames.mat" );
	//auto material2 = renderer.LoadMaterial( "materials/texture_from_zip.mat" );
	//auto material2 = renderer.LoadMaterial( "materials/newscast.mat" );
	//auto material2 = renderer.LoadMaterial( "textures/texpack_1/killblockgeomtrn.png" );

	{
		const auto materialWaitCursor = renderer.LoadMaterial( "materials/wait_cursor.mat" );

		m_meshMovable = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialWaitCursor, glm::vec3( 0.0f, 10.0f, 20.0f ) );
		m_meshMovable->SetScale( { 3.0f, 3.0f, 1.0f } );
		m_scene.AddMesh( m_meshMovable );
	}

	// create small cube of cubes
	{
		const auto material1 = renderer.LoadMaterial( "materials/schnarf.mat" );

		const std::uint16_t cubeSize { 4 };

		for( std::uint16_t i = 0; i < cubeSize; i++ )
		{
			for( std::uint16_t j = 0; j < cubeSize; j++ )
			{
				for( std::uint16_t k = 0; k < cubeSize; k++ )
				{
					const auto mesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material1, glm::vec3( 20.0f + i * 4.0f, ( 0.0f + j * 4.0f ) + 2, -10.0f + k * 4.0f ) );
					mesh->SetScale( { 2.0f, 2.0f, 2.0f } );

					m_scene.AddMesh( mesh );
				}
			}
		}
	}

	{
		const auto materialSuperBox = renderer.LoadMaterial( "materials/superBox.mat" );

		{
			const auto m_mesh2 = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, materialSuperBox, glm::vec3( 0.0f, 10.0f, -10.0f ) );
			m_mesh2->SetScale( { 10.0f, 10.0f, 10.0f } );
			m_scene.AddMesh( m_mesh2 );
		}

		// create big cube of cubes
		{
			const std::uint16_t cubeSize { 12 };

			for( std::uint16_t i = 0; i < cubeSize; i++ )
			{
				for( std::uint16_t j = 0; j < cubeSize; j++ )
				{
					for( std::uint16_t k = 0; k < cubeSize; k++ )
					{
						const auto mesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, materialSuperBox, glm::vec3( 20.0f + i * 4.0f, ( 0.0f + j * 4.0f ) + 2, 50.0f + k * 4.0f ) );
						mesh->SetScale( { 2.0f, 2.0f, 2.0f } );

						m_scene.AddMesh( mesh );
					}
				}
			}
		}
	}

	{
		const auto fireMaterial = renderer.LoadMaterial( "materials/flames.mat" );
		const auto mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, fireMaterial, glm::vec3( -5.0f, 10.0f, 1.0f ) );
		mesh->SetScale( { 4.0f, 8.0f, 1.0f } );
		m_scene.AddMesh( mesh );
	}

	{
		const auto greenMaterial = renderer.LoadMaterial( "materials/green.mat" );
		const auto mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, greenMaterial, glm::vec3( -4.0f, 10.0f, 1.0f ) );
		mesh->SetScale( { 2.0f, 2.0f, 1.0f } );
		m_scene.AddMesh( mesh );
	}

	{
		const auto pulseMaterial = renderer.LoadMaterial( "materials/pulse_green_red.mat" );
		m_pulseMesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, pulseMaterial, glm::vec3( 0.0f, 10.0f, 1.0f ) );
		m_pulseMesh->SetScale( { 2.0f, 2.0f, 1.0f } );
		m_scene.AddMesh( m_pulseMesh );
	}

	{
		const auto redMaterial = renderer.LoadMaterial( "materials/red.mat" );
		const auto mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, redMaterial, glm::vec3( 4.0f, 10.0f, 1.0f ) );
		mesh->SetScale( { 2.0f, 2.0f, 1.0f } );
		m_scene.AddMesh( mesh );
	}

	{
		const auto material3 = renderer.LoadMaterial( "materials/sky.mat" );

		m_skyboxMesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material3 );
		m_scene.AddMesh( m_skyboxMesh );
	}

	// TODO port to SoundManager or something like this
	//const auto testSound = soundManager.Load( "music/rise_of_spirit.ogg" );
	//soundManager.Play( testSound );
}

CStateGame::~CStateGame()
{
}

std::shared_ptr< CState > CStateGame::Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input )
{
	if( input.KeyDown( SDL_SCANCODE_ESCAPE ) )
	{
		logINFO( "pause" );
		return( std::make_shared< CStatePause >( m_filesystem, m_settings, renderer, shared_from_this() ) );
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
		pos.y = 10.0f + ( sin( time / 2000000.0 ) * 5.0f );
		m_pulseMesh->SetPosition( pos );
	}

	/*
	 * move meshMovable
	 */

	if( input.KeyStillDown( SDL_SCANCODE_KP_6 ) )
	{
		glm::vec3 pos = m_meshMovable->Position();
		pos.x += spp;
		m_meshMovable->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_4 ) )
	{
		glm::vec3 pos = m_meshMovable->Position();
		pos.x -= spp;
		m_meshMovable->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_8 ) )
	{
		glm::vec3 pos = m_meshMovable->Position();
		pos.y += spp;
		m_meshMovable->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_2 ) )
	{
		glm::vec3 pos = m_meshMovable->Position();
		pos.y -= spp;
		m_meshMovable->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_PLUS ) )
	{
		glm::vec3 pos = m_meshMovable->Position();
		pos.z += spp;
		m_meshMovable->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_MINUS ) )
	{
		glm::vec3 pos = m_meshMovable->Position();
		pos.z -= spp;
		m_meshMovable->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_5 ) )
	{
		m_meshMovable->SetPosition( glm::vec3() );
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

	soundManager.SetListener( m_cameraFree );

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
		std::replace( datetime.begin(), datetime.end(), ':', '.' );

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
		m_meshMovable->SetOrientation( glm::vec3( m_yrot / 2, m_xrot / 2, 0.0f ) );
	}

	m_rotx_ps = input.MouseDeltaX();
	m_roty_ps = input.MouseDeltaY();

	m_xrot += m_rotx_ps;
	m_yrot += m_roty_ps;

	// m_cameraFree->SetDirection( mesh->Position() - m_cameraFree->Position() );

	m_skyboxMesh->SetPosition( m_cameraFree->Position() );

	return( shared_from_this() );
}
