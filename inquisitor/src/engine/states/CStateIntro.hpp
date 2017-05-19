#ifndef CSTATEINTRO_HPP
#define CSTATEINTRO_HPP

#include "CState.hpp"

#include "src/engine/renderer/camera/CCamera.hpp"

class CStateIntro final : public CState
{
public:
	CStateIntro( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems );
	~CStateIntro();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	const std::uint64_t m_startTime;

	const std::shared_ptr< CSound > m_startupSound;

	const float m_waitTime;

	std::shared_ptr< CMesh > m_logoMesh;
};

#endif // CSTATEINTRO_HPP
