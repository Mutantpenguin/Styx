#pragma once

#include "CState.hpp"

#include "src/engine/sound/CSoundSource.hpp"

class CStateMainMenu final : public CState
{
private:
	CStateMainMenu( const CStateMainMenu& rhs );
	CStateMainMenu& operator=( const CStateMainMenu& rhs );

public:
	CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	~CStateMainMenu();

	virtual std::shared_ptr< CState > OnUpdate( void ) override;

private:
	enum class eMenuState
	{
		START,
		EXIT
	};

	eMenuState m_currentState { eMenuState::START };

	std::shared_ptr< CEntity > m_startEntity;
	std::shared_ptr< CEntity > m_exitEntity;

	const std::shared_ptr< const CSoundSource > m_buttonChangeSound;

	std::shared_ptr< const CSoundSource > m_backgroundMusic;
};
