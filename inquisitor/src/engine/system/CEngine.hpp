#ifndef CENGINE_HPP
#define CENGINE_HPP

#include "src/engine/sdl/CSDL.hpp"

#include "src/engine/system/CGameInfo.hpp"
#include "src/engine/system/CFileSystem.hpp"
#include "src/engine/system/CSettings.hpp"
#include "src/engine/system/CWindow.hpp"

#include "src/engine/system/CEngineSystems.hpp"

#include "src/engine/resource/CResourceCacheManager.hpp"

#include "src/engine/states/CState.hpp"

class CEngine final
{
public:
	CEngine( const char *argv0, const std::string &gameDirectory, const std::string &settingsFile );
	~CEngine( void );

	void    Run( void );

	static std::string GetVersionString( void );

private:
	CEngine( const CEngine &rhs ) = delete;
	CEngine& operator = ( const CEngine &rhs ) = delete;

	static const std::string m_name;
	static const std::uint16_t m_version_major;
	static const std::uint16_t m_version_minor;
	static const std::uint16_t m_version_patch;
	static const std::string m_status;

	const CGameInfo		m_gameInfo;

	const CFileSystem	m_filesystem;
	const CSettings		m_settings;

	const CSDL	m_sdl;

	const CWindow	m_window;

	CEngineSystems m_engineSystems;

	CResourceCacheManager m_resourceCacheManager;

	std::shared_ptr< CState > m_currentState;
};

#endif // CENGINE_HPP
