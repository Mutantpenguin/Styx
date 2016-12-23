#ifndef CSTATE_HPP
#define CSTATE_HPP

#include <memory>

#include "src/engine/renderer/CRenderer.hpp"

#include "src/engine/sound/CSoundManager.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/system/CFileSystem.hpp"
#include "src/engine/system/CInput.hpp"
#include "src/engine/system/CSettings.hpp"

class CState : public std::enable_shared_from_this< CState >
{
private:
	CState( const CState &rhs ) = delete;
	CState& operator = ( const CState &rhs ) = delete;

protected:
	CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings );
	virtual ~CState() {};

public:
	virtual std::shared_ptr< CState > Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input ) = 0;

	virtual void Render( const CRenderer &renderer, const std::uint64_t time ) const;

	virtual const CScene &Scene( void ) const final;

	virtual const std::string &Name( void ) const final;

protected:
	const std::string	m_name;

	const CFileSystem	&m_filesystem;
	const CSettings		&m_settings;

	CScene m_scene;
};

#endif // CSTATE_HPP
