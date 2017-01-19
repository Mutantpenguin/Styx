#include "src/engine/logger/CLogTargetMessageBox.hpp"

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

void CLogTargetMessageBox::Log( const std::unique_ptr< const CLogger::logEntry > &entry )
{
	if( e_loglevel::ERROR == entry->m_logLevel )
	{
		const SDL_MessageBoxColor color = { 255, 0, 0 };

		SDL_MessageBoxData data;
		SDL_MessageBoxButtonData button;
		SDL_MessageBoxColorScheme colorScheme;

		SDL_zero( data );
		data.flags = SDL_MESSAGEBOX_ERROR;
		data.title = CLogger::LogLevelToString( entry->m_logLevel ).c_str();
		data.message = entry->m_message.c_str();
		data.numbuttons = 1;
		data.buttons = &button;
		data.window = nullptr;
		data.colorScheme = &colorScheme;

		SDL_zero( button );
		button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
		button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
		button.text = "OK";

		SDL_zero( colorScheme );
		colorScheme.colors[ SDL_MESSAGEBOX_COLOR_BACKGROUND ] = color;
		colorScheme.colors[ SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND ] = color;

		SDL_ShowMessageBox( &data, nullptr );
	}
}
