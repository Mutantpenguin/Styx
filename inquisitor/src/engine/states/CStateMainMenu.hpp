#ifndef CSTATEMAINMENU_HPP
#define CSTATEMAINMENU_HPP

#include "CState.hpp"

#include "src/engine/sound/CSoundSource.hpp"

class CStateMainMenu final : public CState
{
private:
	CStateMainMenu( const CStateMainMenu& rhs );
	CStateMainMenu& operator=( const CStateMainMenu& rhs );

public:
	CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems );
	~CStateMainMenu();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	enum class eMenuState
	{
		START,
		EXIT
	};

	eMenuState m_currentState { eMenuState::START };

	std::shared_ptr< CMesh > m_startMesh;
	std::shared_ptr< CMesh > m_exitMesh;

	const std::shared_ptr< const CSoundSource > m_buttonChangeSound;
};

#endif // CSTATEMAINMENU_HPP
