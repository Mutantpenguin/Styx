#pragma once

#include "src/core/Types.hpp"

#include "src/sdl/CSDL.hpp"

#include "src/system/CGameInfo.hpp"
#include "src/system/CFileSystem.hpp"
#include "src/system/CSettings.hpp"
#include "src/system/CWindow.hpp"

#include "src/system/CEngineInterface.hpp"

#include "src/states/CState.hpp"

class CEngine final
{
public:
	CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile );
	~CEngine();

	void Run();

	static std::string GetVersionString();

private:
	CEngine( const CEngine &rhs ) = delete;
	CEngine& operator = ( const CEngine &rhs ) = delete;

	static const std::string	m_name;
	static const u16			m_version_major;
	static const u16			m_version_minor;
	static const u16 			m_version_patch;
	static const std::string	m_status;

	const CGameInfo		m_gameInfo;

	const CFileSystem	m_filesystem;
	const CSettings		m_settings;

	const CSDL	m_sdl;

	const CWindow	m_window;

	CEngineInterface m_engineInterface;
};
