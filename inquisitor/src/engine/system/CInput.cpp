#include "CInput.hpp"

#include "../logger/CLogger.hpp"

CInput::CInput( const CSettings &settings, const CFileSystem &filesystem )
{
	m_keys = SDL_GetKeyboardState( &m_keyCount );
	m_oldKeys = new Uint8[ m_keyCount ];

	// get information about joysticks
	if( SDL_InitSubSystem( SDL_INIT_JOYSTICK ) )
	{
		LOG( logINFO ) << "initializing SDL joystick subsystem failed: " << SDL_GetError();
	}
	else
	{
		if( SDL_JoystickEventState( SDL_ENABLE ) != SDL_ENABLE )
		{
			LOG( logDEBUG ) << "cannot enable joystick event polling!";
		}

		if( settings.input.controller_file.empty() )
		{
			LOG( logWARNING ) << "no file specified for controller mappings";
		}
		else
		{
			if( filesystem.Exists( settings.input.controller_file ) )
			{
				switch( SDL_GameControllerAddMapping( filesystem.LoadTextFileToBuffer( settings.input.controller_file ).c_str() ) )
				{
					case 1:
						LOG( logINFO ) << "added controller mappings from file '" << settings.input.controller_file << "'";
						break;

					case -1:
						LOG( logWARNING ) << "unable to add controller mappings: " << SDL_GetError();
						break;
				}
			}
			else
			{
				LOG( logWARNING ) << "file '" << settings.input.controller_file << "' for controller mappings doesn't exist";
			}
		}

		const int js_num = SDL_NumJoysticks();
		if( js_num < 0 )
		{
			LOG( logWARNING ) << "unable to retrieve number of attached joysticks: " << SDL_GetError();
		}
		else
		{
			LOG( logINFO ) << "'" << js_num << "' joysticks available";
			for( int i = 0; i < js_num; ++i )
			{
				LOG( logDEBUG ) << "Joystick #" << i;

				if( SDL_IsGameController( i ) )
				{
					SDL_GameController *controller = SDL_GameControllerOpen( i );
					if( nullptr == controller )
					{
						LOG( logERROR ) << "unable to open controller #" << i << ": " << SDL_GetError();
					}
					else
					{
						LOG( logDEBUG ) << "Name: " << SDL_GameControllerName( controller );
						LOG( logDEBUG ) << "Mapped as : " << SDL_GameControllerMapping( controller );

						SDL_Joystick *joystick = SDL_GameControllerGetJoystick( controller );
						LOG( logDEBUG ) << "Layout: " << SDL_JoystickNumAxes( joystick ) << " Axes / " << SDL_JoystickNumButtons( joystick ) << " Buttons / " << SDL_JoystickNumBalls( joystick ) << " Trackballs / " << SDL_JoystickNumHats( joystick ) << " Hat Switches / " << ( ( SDL_JoystickIsHaptic( joystick ) == 1 ) ? " is haptic" : "is not haptic" );

						SDL_GameControllerClose( controller );
					}
				}
				else
				{
					SDL_Joystick *joystick = SDL_JoystickOpen( i );
					if( nullptr == joystick )
					{
						LOG( logERROR ) << "unable to open joystick #" << i << ": " << SDL_GetError();
					}
					else
					{
						LOG( logDEBUG ) << "Name: " << SDL_JoystickName( joystick );
						LOG( logDEBUG ) << "Layout: " << SDL_JoystickNumAxes( joystick ) << " Axes / " << SDL_JoystickNumButtons( joystick ) << " Buttons / " << SDL_JoystickNumBalls( joystick ) << " Trackballs / " << SDL_JoystickNumHats( joystick ) << " Hat Switches / " << ( ( SDL_JoystickIsHaptic( joystick ) == 1 ) ? " is haptic" : "is not haptic" );

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

