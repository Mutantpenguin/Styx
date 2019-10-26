#include <array>

#include "CWindow.hpp"

#include "src/logger/CLogger.hpp"

#include "src/helper/image/ImageHandler.hpp"

#include "src/core/StyxException.hpp"

CWindow::CWindow( const CSettings &settings, const CFileSystem &filesystem, const std::string &windowTitle, const std::string &iconPath )
{
	if( SDL_InitSubSystem( SDL_INIT_VIDEO ) )
	{
		THROW_STYX_EXCEPTION( "initializing SDL video subsystem failed: {0}", SDL_GetError() )
	}

	u8 showWindowOnDisplay = settings.renderer.window.display;
	const s16 numberOfDisplays = SDL_GetNumVideoDisplays();
	if( numberOfDisplays < 0 )
	{
		THROW_STYX_EXCEPTION( "couldn't get number of displays: {0}", SDL_GetError() )
	}
	else
	{
		logINFO( "number of displays: {0}", numberOfDisplays );

		if( showWindowOnDisplay >= numberOfDisplays )
		{
			logWARNING( "display is set to the non existing display '{0}'", showWindowOnDisplay );
			showWindowOnDisplay = 0;
		}

		logINFO( "using display '{0} - {1}'", showWindowOnDisplay, SDL_GetDisplayName( showWindowOnDisplay ) );
	}

	// 32 bpp
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,	8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,	8 );

	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,	24 );

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	#ifdef STYX_DEBUG
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG );
	#endif

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );

	SDL_GL_SetAttribute( SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1 );

	int window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	#ifndef STYX_DEBUG
		window_flags |= SDL_WINDOW_INPUT_GRABBED;
	#endif

	if( settings.renderer.window.fullscreen )
	{
		window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS;
	}

	m_SDL_window = SDL_CreateWindow(	windowTitle.c_str(),
										SDL_WINDOWPOS_CENTERED_DISPLAY( showWindowOnDisplay ),
										SDL_WINDOWPOS_CENTERED_DISPLAY( showWindowOnDisplay ),
										settings.renderer.window.size.width,
										settings.renderer.window.size.height,
										window_flags );

	if( nullptr == m_SDL_window )
	{
		THROW_STYX_EXCEPTION( "creating SDL window failed: {0}", SDL_GetError() )
	}

	if( !iconPath.empty() )
	{
		const std::shared_ptr<const CImage> image = ImageHandler::Load( filesystem, iconPath, 256, true );
		if( image )
		{
			const auto pixelFormat = ( image->BPP() == 32 ) ? SDL_PIXELFORMAT_RGBA32 : SDL_PIXELFORMAT_RGB24;

			SDL_Surface *gameIcon = SDL_CreateRGBSurfaceWithFormatFrom( const_cast<void*>( static_cast<const void*>( image->RawPixelData() ) ), image->Size().width, image->Size().height, image->BPP(), image->Pitch(), pixelFormat );

			if( nullptr != gameIcon )
			{
				SDL_SetWindowIcon( m_SDL_window, gameIcon );
				SDL_FreeSurface( gameIcon );
			}
			else
			{
				logWARNING( "creation of game-icon '{0}' failed: {1}", iconPath, SDL_GetError() );
			}
		}
		else
		{
			logWARNING( "loading of game-icon '{0}' failed", iconPath );
		}
	}
	else
	{
		logWARNING( "game specified no window-icon" );
	}

	m_SDL_GL_renderContext = SDL_GL_CreateContext( m_SDL_window );
	if( nullptr == m_SDL_GL_renderContext )
	{
		THROW_STYX_EXCEPTION( "creating the GL context for rendering failed: {0}", SDL_GetError() )
	}

	m_SDL_GL_threadContext = SDL_GL_CreateContext( m_SDL_window );
	if( nullptr == m_SDL_GL_threadContext )
	{
		THROW_STYX_EXCEPTION( "creating the GL context for threaded loading failed: {0}", SDL_GetError() )
	}

	if( SDL_GL_MakeCurrent( m_SDL_window, m_SDL_GL_renderContext ) )
	{
		THROW_STYX_EXCEPTION( "making the GL render context current failed: {0}", SDL_GetError() )
	}

	int doubleBuffered = 0;
	if(	( SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &doubleBuffered ) < 0 )
		||
		( 0 == doubleBuffered ) )
	{
		THROW_STYX_EXCEPTION( "couldn't get a double-buffered GL context: {0}", SDL_GetError() )
	}

	if( settings.renderer.window.vsync )
	{
		if( SDL_GL_SetSwapInterval( -1 ) != 0 )
		{
			logINFO( "late swap tearing not available: {0}", SDL_GetError() );

			if( SDL_GL_SetSwapInterval( 1 ) != 0 )
			{
				logWARNING( "vsync not available: {0}", SDL_GetError() );
			}
		}
	}
	else
	{
		SDL_GL_SetSwapInterval( 0 );
		logINFO( "vsync disabled" );
	}

	if( settings.renderer.window.gamma > 0.0f )
	{
		std::array<Uint16, 256> ramp;
		SDL_CalculateGammaRamp( settings.renderer.window.gamma, ramp.data() );
		if( SDL_SetWindowGammaRamp( m_SDL_window, ramp.data(), ramp.data(), ramp.data() ) != 0 )
		{
			logWARNING( "setting the gamma ramp failed: {0}", SDL_GetError() );
		}
	}

	#ifndef STYX_DEBUG
	    logDEBUG( "using relative mouse-mode" );
		SDL_SetRelativeMouseMode( SDL_FALSE );
	#endif
}

CWindow::~CWindow()
{
	if( nullptr != m_SDL_GL_renderContext )
	{
		SDL_GL_DeleteContext( m_SDL_GL_renderContext );
	}

	if( nullptr != m_SDL_GL_threadContext )
	{
		SDL_GL_DeleteContext( m_SDL_GL_threadContext );
	}

	if( nullptr != m_SDL_window )
	{
		SDL_DestroyWindow( m_SDL_window );
	}

	if( SDL_WasInit( SDL_INIT_VIDEO ) != 0 )
	{
		SDL_QuitSubSystem( SDL_INIT_VIDEO );
	}
}

void CWindow::Update() const
{
	SDL_GL_SwapWindow( m_SDL_window );
}
