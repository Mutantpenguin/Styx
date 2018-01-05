#ifndef CSTATEINTRO_HPP
#define CSTATEINTRO_HPP

#include "CState.hpp"
#include "src/engine/system/CTimer.hpp"

#include "src/engine/sound/CSoundSource.hpp"

class CStateIntro final : public CState
{
private:
	CStateIntro( const CStateIntro& rhs );
	CStateIntro& operator=( const CStateIntro& rhs );

public:
	CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	~CStateIntro();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	const std::uint64_t m_startTime;

	const std::shared_ptr< const CSoundSource > m_introSound;

	const float m_introDuration;

	std::shared_ptr< CEntity > m_logoEntity;
};

#endif // CSTATEINTRO_HPP
