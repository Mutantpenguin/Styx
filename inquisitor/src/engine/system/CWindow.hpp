#ifndef CWINDOW_HPP
#define CWINDOW_HPP

#include <exception>

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/engine/system/CSettings.hpp"

#include "src/engine/helper/CSize.hpp"

class CWindow final
{
public:
	CWindow( const CSettings &settings, const CFileSystem &filesystem, const std::string &windowTitle, const std::string &iconPath );
	~CWindow( void );

	void Update( void ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	SDL_Window		*m_SDL_window { nullptr };
	SDL_GLContext	m_SDL_GL_context;
};

#endif // CWINDOW_HPP
