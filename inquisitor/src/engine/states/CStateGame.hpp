#ifndef CSTATEGAME_HPP
#define CSTATEGAME_HPP

#include "src/engine/states/CState.hpp"

#include "src/engine/states/CStatePause.hpp"

#include "src/engine/renderer/camera/CCameraFree.hpp"

class CStateGame final : public CState
{
public:
	CStateGame( const CFileSystem &filesystem, const CSettings &settings, CSoundManager &soundManager, CRenderer &renderer );
	~CStateGame();

	virtual std::shared_ptr< CState > Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input ) override;

private:
	std::shared_ptr< CCameraFree > m_cameraFree;

	float	m_xrot = 0.0f;
	float	m_yrot = 0.0f;
	float	m_rotx_ps = 0.0f;
	float	m_roty_ps = 0.0f;

	std::shared_ptr< CMesh >	m_meshMovable;
	std::shared_ptr< CMesh >	m_skyboxMesh;
	std::shared_ptr< CMesh >	m_pulseMesh;
};

#endif // CSTATEGAME_HPP
