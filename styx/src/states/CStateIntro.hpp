#pragma once

#include "src/helper/Types.hpp"

#include "CState.hpp"
#include "src/system/CTimer.hpp"

#include "src/sound/CSoundSource.hpp"

class CStateIntro final : public CState
{
private:
	CStateIntro( const CStateIntro& rhs );
	CStateIntro& operator=( const CStateIntro& rhs );

public:
	CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	~CStateIntro();

	virtual std::shared_ptr< CState > OnUpdate() override;

private:
	const std::shared_ptr< const CSoundSource > m_introSound;

	const f16 m_introDuration;

	std::shared_ptr< CEntity > m_logoEntity;
};
