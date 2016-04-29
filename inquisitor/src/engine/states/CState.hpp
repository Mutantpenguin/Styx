#ifndef CSTATE_HPP
#define CSTATE_HPP

#include <memory>

#include "../renderer/CRenderer.hpp"

#include "../sound/CSoundManager.hpp"

#include "../scene/CScene.hpp"

#include "../system/CFileSystem.hpp"
#include "../system/CInput.hpp"
#include "../system/CSettings.hpp"

class CState : public std::enable_shared_from_this< CState >
{
private:
	CState( const CState &rhs ) = delete;
	CState& operator = ( const CState &rhs ) = delete;

protected:
	CState( const CFileSystem &filesystem, const CSettings &settings ) :
		m_filesystem { filesystem },
		m_settings { settings }
	{};
	virtual ~CState() {};

public:
	virtual std::shared_ptr< CState > Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input ) = 0;

	inline const CScene &Scene( void ) const
	{
		return( m_scene );
	}

protected:
	const CFileSystem	&m_filesystem;
	const CSettings		&m_settings;

	CScene m_scene;
};

#endif // CSTATE_HPP
