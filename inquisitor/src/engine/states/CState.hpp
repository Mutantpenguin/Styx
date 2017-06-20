#ifndef CSTATE_HPP
#define CSTATE_HPP

#include <memory>

#include "src/engine/system/CEngineSystems.hpp"

#include "src/engine/renderer/CFrameBuffer.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/system/CFileSystem.hpp"
#include "src/engine/system/CSettings.hpp"

class CState : public std::enable_shared_from_this< CState >
{
private:
	CState( const CState &rhs ) = delete;
	CState& operator = ( const CState &rhs ) = delete;

protected:
	CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems );
	virtual ~CState() {};

public:
	[[nodiscard]] virtual std::shared_ptr< CState > Update( void ) = 0;

	[[nodiscard]] virtual const CScene &Scene( void ) const final;

	[[nodiscard]] virtual const std::string &Name( void ) const final;

	[[nodiscard]] const CFrameBuffer &FrameBuffer( void ) const;

protected:
	const std::string	m_name;

	const CFrameBuffer m_frameBuffer;

	const CFileSystem	&m_filesystem;
	const CSettings		&m_settings;

	CScene m_scene;

	CEngineSystems &m_engineSystems;
};

#endif // CSTATE_HPP
