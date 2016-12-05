#include "CStateGame.hpp"

#include <algorithm>

#include "../helper/Date.hpp"
#include "../helper/geom/Primitives.hpp"
#include "../helper/image/ImageHandler.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "../sound/CSound.hpp"
#include "../sound/SoundHandler.hpp"

CStateGame::CStateGame( const CFileSystem &filesystem, const CSettings &settings, CSoundManager &soundManager, CRenderer &renderer ) :
	CState( "game", filesystem, settings )
{
	renderer.SetClearColor( CColor( 0.0f, 0.0f, 4.0f, 0.0f ) );

	m_camera = std::make_shared< CCamera >( m_settings.renderer.window.aspect_ratio, 90.0f, 0.1f, 100.0f, glm::vec3( 0.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, -10.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

	m_scene.Camera( m_camera );

	soundManager.SetListener( m_camera );

	{
		std::shared_ptr< CMaterial > material1;
		std::shared_ptr< CMaterial > material2;
		material1 = renderer.LoadMaterial( "materials/schnarf.mat" );
		material2 = renderer.LoadMaterial( "materials/wait_cursor.mat" );
		//material2 = renderer.LoadMaterial( "materials/flames.mat" );
		//material2 = renderer.LoadMaterial( "materials/texture_from_zip.mat" );
		//material2 = renderer.LoadMaterial( "materials/newscast.mat" );
		//material2 = renderer.LoadMaterial( "textures/texpack_1/killblockgeomtrn.png" );

		mesh = std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, material2, glm::vec3( 3.0f, 3.0f, 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) );
		m_scene.AddMesh( mesh );

		mesh2 = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material1, glm::vec3( 10.0f, 10.0f, 10.0f ), glm::vec3( 0.0f, 0.0f, -10.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) );
		m_scene.AddMesh( mesh2 );

		{
			const std::uint16_t cubeSize { 4 };

			for( std::uint16_t i = 0; i < cubeSize; i++ )
			{
				for( std::uint16_t j = 0; j < cubeSize; j++ )
				{
					for( std::uint16_t k = 0; k < cubeSize; k++ )
					{
						m_scene.AddMesh( std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material1, glm::vec3( 2.0f, 2.0f, 2.0f ), glm::vec3( 20.0f + i * 4.0f, 0.0f + j * 4.0f, -10.0f + k * 4.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) ) );
					}
				}
			}
		}

		{
			//const std::uint16_t cubeSize { 24 };
			const std::uint16_t cubeSize { 4 };

			for( std::uint16_t i = 0; i < cubeSize; i++ )
			{
				for( std::uint16_t j = 0; j < cubeSize; j++ )
				{
					for( std::uint16_t k = 0; k < cubeSize; k++ )
					{
						m_scene.AddMesh( std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material1, glm::vec3( 2.0f, 2.0f, 2.0f ), glm::vec3( 20.0f + i * 4.0f, -25.0f + j * 4.0f, 50.0f + k * 4.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) ) );
					}
				}
			}
		}
	}

	{
		std::shared_ptr< CMaterial > fireMaterial = renderer.LoadMaterial( "materials/flames.mat" );
		m_scene.AddMesh( std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, fireMaterial, glm::vec3( 4.0f, 8.0f, 1.0f ), glm::vec3( -5.0f, 0.0f, 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) ) );
	}

	{
		std::shared_ptr< CMaterial > blueMaterial = renderer.LoadMaterial( "materials/blue.mat" );
		m_scene.AddMesh( std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, blueMaterial, glm::vec3( 2.0f, 2.0f, 1.0f ), glm::vec3( 0.0f, 10.0f, 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) ) );
	}

	{
		std::shared_ptr< CMaterial > redMaterial = renderer.LoadMaterial( "materials/red.mat" );
		m_scene.AddMesh( std::make_shared< CMesh >( GL_TRIANGLE_STRIP, Primitives::cube, redMaterial, glm::vec3( 2.0f, 2.0f, 1.0f ), glm::vec3( 4.0f, 10.0f, 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) ) );
	}

	{
		std::shared_ptr< CMaterial > material3 = renderer.LoadMaterial( "materials/sky.mat" );

		skyboxMesh = std::make_shared< CMesh >( GL_TRIANGLES, Primitives::cube, material3, glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) );
		m_scene.AddMesh( skyboxMesh );
	}

	// TODO port to SoundManager or something like this
	//std::shared_ptr< CSound > blah = SoundHandler::Load( m_filesystem, "music/rise_of_spirit.ogg" );
	//soundManager.Play( blah );
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

	/*
	 * move mesh
	 */

	if( input.KeyStillDown( SDL_SCANCODE_KP_6 ) )
	{
		glm::vec3 pos = mesh->Position();
		pos.x += spp;
		mesh->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_4 ) )
	{
		glm::vec3 pos = mesh->Position();
		pos.x -= spp;
		mesh->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_8 ) )
	{
		glm::vec3 pos = mesh->Position();
		pos.y += spp;
		mesh->SetPosition( pos );
	}
	if( input.KeyStillDown( SDL_SCANCODE_KP_2 ) )
	{
		glm::vec3 pos = mesh->Position();
		pos.y -= spp;
		mesh->SetPosition( pos );
	}

	if(	input.KeyStillDown( SDL_SCANCODE_KP_PLUS )
		||
		input.KeyStillDown( SDL_SCANCODE_PAGEUP ) )
	{
		glm::vec3 pos = mesh->Position();
		pos.z += spp;
		mesh->SetPosition( pos );
	}
	if(	input.KeyStillDown( SDL_SCANCODE_KP_MINUS )
		||
		input.KeyStillDown( SDL_SCANCODE_PAGEDOWN ) )
	{
		glm::vec3 pos = mesh->Position();
		pos.z -= spp;
		mesh->SetPosition( pos );
	}

	if( input.KeyStillDown( SDL_SCANCODE_KP_5 ) )
	{
		mesh->SetPosition( glm::vec3() );
	}

	/*
	 * move camera
	 */

	const float ctrlPressedMult = input.KeyStillDown( SDL_SCANCODE_LCTRL ) ? 10 : 1;

/*
	if( input.MouseStillDown( SDL_BUTTON_LEFT) )
	{
		m_camera->M
	}
*/
	if( input.KeyStillDown( SDL_SCANCODE_A ) )
	{
		m_camera->MoveLeft( spp * ctrlPressedMult );
	}

	if( input.KeyStillDown( SDL_SCANCODE_D ) )
	{
		m_camera->MoveRight( spp * ctrlPressedMult );
	}

	if( input.KeyStillDown( SDL_SCANCODE_W ) )
	{
		m_camera->MoveForward( spp * ctrlPressedMult );
	}

	if( input.KeyStillDown( SDL_SCANCODE_S ) )
	{
		m_camera->MoveBackward( spp * ctrlPressedMult );
	}

	if( input.KeyStillDown( SDL_SCANCODE_SPACE ) )
	{
		m_camera->MoveUp( spp * ctrlPressedMult );
	}

	if( input.KeyStillDown( SDL_SCANCODE_LSHIFT ) )
	{
		m_camera->MoveDown( spp * ctrlPressedMult );
	}

	soundManager.SetListener( m_camera );

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

		std::string datetime = Date::GetCurrentDateString();
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

	mesh->SetOrientation( glm::vec3( m_yrot / 2, m_xrot / 2, 0.0f ) );

	m_rotx_ps = input.MouseDeltaX();
	m_roty_ps = input.MouseDeltaY();

	m_xrot += m_rotx_ps;
	m_yrot += m_roty_ps;

	m_camera->LookAt( mesh->Position() );

	skyboxMesh->SetPosition( m_camera->Position() );

	return( shared_from_this() );
}
