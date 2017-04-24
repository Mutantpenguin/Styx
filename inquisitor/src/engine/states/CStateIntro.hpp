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

	const float m_waitTime = 8000000;

	std::shared_ptr< CMesh > m_mesh;
};

#endif // CSTATEINTRO_HPP
