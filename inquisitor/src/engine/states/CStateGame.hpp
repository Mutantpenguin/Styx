#ifndef CSTATEGAME_HPP
#define CSTATEGAME_HPP

#include "src/engine/states/CState.hpp"

#include "src/engine/states/CStatePause.hpp"

#include "src/engine/scene/camera/CCameraFree.hpp"

#include "src/engine/sound/CSoundSource.hpp"

class CStateGame final : public CState
{
private:
	CStateGame( const CStateGame& rhs );
	CStateGame& operator=( const CStateGame& rhs );

public:
	CStateGame( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	~CStateGame();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	std::shared_ptr< CCameraFree > m_cameraFree;

	float	m_rotx_ps = 0.0f;
	float	m_roty_ps = 0.0f;

	std::shared_ptr< CEntity >	m_movableEntity;
	std::shared_ptr< CEntity >	m_skyboxEntity;
	std::shared_ptr< CEntity >	m_pulseEntity;

	std::shared_ptr< const CSoundSource > m_backgroundMusic;
};

#endif // CSTATEGAME_HPP
