#ifndef CWINDOW_HPP
#define CWINDOW_HPP

#include <SDL2/SDL.h>

#include "../system/CSettings.hpp"

#include "../helper/CSize.hpp"

class CWindow final
{
public:
	CWindow( const CSettings &settings, const CFileSystem &filesystem, const std::string &windowTitle, const std::string &iconPath );
	virtual ~CWindow( void );

	virtual void	Update( void );

private:
	SDL_Window		*m_SDL_window { nullptr };
	SDL_GLContext	m_SDL_GL_context;
};

#endif // CWINDOW_HPP
