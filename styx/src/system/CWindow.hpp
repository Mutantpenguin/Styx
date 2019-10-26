#pragma once

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/system/CSettings.hpp"

#include "src/helper/CSize.hpp"

class CWindow final
{
public:
	CWindow( const CSettings &settings, const CFileSystem &filesystem, const std::string &windowTitle, const std::string &iconPath );
	~CWindow();

	void Update() const;

private:
	CWindow( const CWindow &rhs ) = delete;
	CWindow& operator = ( const CWindow &rhs ) = delete;

	SDL_Window		*m_SDL_window { nullptr };
	SDL_GLContext	m_SDL_GL_context;
};
