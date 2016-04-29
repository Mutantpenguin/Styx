#ifndef CSTATEINTRO_HPP
#define CSTATEINTRO_HPP

#include "CState.hpp"

#include "../renderer/CCamera.hpp"

class CStateIntro final : public CState
{
public:
	CStateIntro( const CFileSystem &filesystem, const CSettings &settings, const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer );
	~CStateIntro();

	virtual std::shared_ptr< CState > Update( const std::uint64_t time, CSoundManager& soundManager, CRenderer& renderer, const CInput& input ) override;

private:
	const std::uint64_t m_startTime;

	const float m_waitTime = 7000000;

	std::shared_ptr< CCamera > m_camera;

	std::shared_ptr< CMesh > mesh;
};

#endif // CSTATEINTRO_HPP
