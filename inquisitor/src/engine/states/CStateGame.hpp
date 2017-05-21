#ifndef CSTATEGAME_HPP
#define CSTATEGAME_HPP

#include "src/engine/states/CState.hpp"

#include "src/engine/states/CStatePause.hpp"

#include "src/engine/renderer/camera/CCameraFree.hpp"

#include "src/engine/sound/CSoundSource.hpp"

class CStateGame final : public CState
{
public:
	CStateGame( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems );
	~CStateGame();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	std::shared_ptr< CCameraFree > m_cameraFree;

	float	m_xrot = 0.0f;
	float	m_yrot = 0.0f;
	float	m_rotx_ps = 0.0f;
	float	m_roty_ps = 0.0f;

	std::shared_ptr< CMesh >	m_movableMesh;
	std::shared_ptr< CMesh >	m_skyboxMesh;
	std::shared_ptr< CMesh >	m_pulseMesh;

	std::shared_ptr< const CSoundSource > m_backgroundMusic;
};

#endif // CSTATEGAME_HPP
