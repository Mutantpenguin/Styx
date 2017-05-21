#ifndef CSTATEINTRO_HPP
#define CSTATEINTRO_HPP

#include "CState.hpp"

#include "src/engine/sound/CSoundSource.hpp"

class CStateIntro final : public CState
{
public:
	CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems );
	~CStateIntro();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	const std::uint64_t m_startTime;

	const std::shared_ptr< CSoundSource > m_introSound;

	const float m_introDuration;

	std::shared_ptr< CMesh > m_logoMesh;
};

#endif // CSTATEINTRO_HPP
