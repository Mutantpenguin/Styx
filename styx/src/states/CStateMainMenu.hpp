#pragma once

#include "CState.hpp"

#include "src/audio/CAudioSource.hpp"

class CStateMainMenu final : public CState
{
private:
	CStateMainMenu( const CStateMainMenu& rhs );
	CStateMainMenu& operator=( const CStateMainMenu& rhs );

public:
	CStateMainMenu( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	~CStateMainMenu();

	virtual std::shared_ptr<CState> OnUpdate() override;

private:
	enum class eMenuState
	{
		NONE,
		START,
		EXIT
	};

	eMenuState m_currentState { eMenuState::START };

	std::shared_ptr<CEntity> m_startEntity;
	std::shared_ptr<CEntity> m_exitEntity;

	const std::shared_ptr<const CAudioSource> m_buttonChangeSound;

	std::shared_ptr<const CAudioSource> m_backgroundMusic;
};
