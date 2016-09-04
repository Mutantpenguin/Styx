#include "CInput.hpp"

#include "../logger/CLogger.hpp"

CInput::CInput( const CSettings &settings, const CFileSystem &filesystem )
{
	m_keys = SDL_GetKeyboardState( &m_keyCount );
	m_oldKeys = new Uint8[ m_keyCount ];

	// get information about joysticks
	if( SDL_InitSubSystem( SDL_INIT_JOYSTICK ) )
	{
		logINFO( "initializing SDL joystick subsystem failed: {0}", SDL_GetError() );
	}
	else
	{
		if( SDL_JoystickEventState( SDL_ENABLE ) != SDL_ENABLE )
		{
			logDEBUG( "cannot enable joystick event polling!" );
		}

		if( settings.input.controller_file.empty() )
		{
			logWARNING( "no file specified for controller mappings" );
		}
		else
		{
			if( filesystem.Exists( settings.input.controller_file ) )
			{
				switch( SDL_GameControllerAddMapping( filesystem.LoadTextFileToBuffer( settings.input.controller_file ).c_str() ) )
				{
					case 1:
						logINFO( "added controller mappings from file '{0}'", settings.input.controller_file );
						break;

					case -1:
						logWARNING( "unable to add controller mappings: {0}", SDL_GetError() );
						break;
				}
			}
			else
			{
				logWARNING( "file '{0}' for controller mappings doesn't exist", settings.input.controller_file );
			}
		}

		const int js_num = SDL_NumJoysticks();
		if( js_num < 0 )
		{
			logWARNING( "unable to retrieve number of attached joysticks: {0}", SDL_GetError() );
		}
		else
		{
			logINFO( "'{0}' joysticks available", js_num );
			for( int i = 0; i < js_num; ++i )
			{
				logDEBUG( "Joystick #{0}", i );

				if( SDL_IsGameController( i ) )
				{
					SDL_GameController *controller = SDL_GameControllerOpen( i );
					if( nullptr == controller )
					{
						logERROR( "unable to open controller #{0}: {1}", i, SDL_GetError() );
					}
					else
					{
						logDEBUG( "Name: {0}", SDL_GameControllerName( controller ) );
						logDEBUG( "Mapped as: {0}", SDL_GameControllerMapping( controller ) );

						SDL_Joystick *joystick = SDL_GameControllerGetJoystick( controller );
						logDEBUG( "Layout: {0} Axes / {1} Buttons / {2} Trackballs / {3} Hat Switches / {4}", SDL_JoystickNumAxes( joystick ), SDL_JoystickNumButtons( joystick ), SDL_JoystickNumBalls( joystick ), SDL_JoystickNumHats( joystick ), ( ( SDL_JoystickIsHaptic( joystick ) == 1 ) ? " is haptic" : "is not haptic" ) );

						SDL_GameControllerClose( controller );
					}
				}
				else
				{
					SDL_Joystick *joystick = SDL_JoystickOpen( i );
					if( nullptr == joystick )
					{
						logERROR( "unable to open joystick #{0}: {1}", i, SDL_GetError() );
					}
					else
					{
						logDEBUG( "Name: {0}", SDL_JoystickName( joystick ) );
						logDEBUG( "Layout: {0} Axes / {1} Buttons / {2} Trackballs / {3} Hat Switches / {4}", SDL_JoystickNumAxes( joystick ), SDL_JoystickNumButtons( joystick ), SDL_JoystickNumBalls( joystick ), SDL_JoystickNumHats( joystick ), ( ( SDL_JoystickIsHaptic( joystick ) == 1 ) ? " is haptic" : "is not haptic" ) );

						SDL_JoystickClose( joystick );
					}
				}
			}
		}
	}

	SDL_PumpEvents();
}

CInput::~CInput( void )
{
	if( SDL_WasInit( SDL_INIT_JOYSTICK ) != 0 )
	{
		SDL_QuitSubSystem( SDL_INIT_JOYSTICK );
	}

	m_keys = nullptr;
	if( m_oldKeys )
	{
		delete [] m_oldKeys;
		m_oldKeys = nullptr;
	}
}

void CInput::Update( void )
{
	m_oldButtons = m_buttons;
	m_buttons = SDL_GetRelativeMouseState( &m_dX, &m_dY );
	memcpy( m_oldKeys, m_keys, sizeof( Uint8 ) * m_keyCount );

	SDL_PumpEvents();
}

