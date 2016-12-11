#ifndef CENGINE_HPP
#define CENGINE_HPP

#include "src/engine/sdl/CSDL.hpp"

#include "CGameInfo.hpp"
#include "CFileSystem.hpp"
#include "CSettings.hpp"
#include "CInput.hpp"
#include "CTimer.hpp"
#include "CWindow.hpp"

#include "src/engine/sound/CSoundManager.hpp"

#include "src/engine/renderer/CRenderer.hpp"

#include "src/engine/states/CState.hpp"

class CEngine final
{
public:
	CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile );
	~CEngine( void );

	void    Run( void );

	static const std::string GetVersionString( void );

private:
	const CGameInfo		m_gameInfo;
	const CFileSystem	m_filesystem;
	const CSettings		m_settings;

	static const std::string m_name;
	static const std::string m_version;
	static const std::string m_status;

	CSDL	m_sdl;

	CWindow		m_window;
	CInput		m_input;
	CRenderer	m_renderer;

	CSoundManager	m_soundManager;

	std::shared_ptr< CState > m_currentState;

	CTimer	m_globalTimer;
};

#endif // CENGINE_HPP
