#pragma once

#include "src/core/Types.hpp"

#include "src/states/CState.hpp"

#include "src/audio/CAudioSource.hpp"

class CStateGame final : public CState
{
private:
	CStateGame( const CStateGame& rhs );
	CStateGame& operator=( const CStateGame& rhs );

public:
	CStateGame( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	~CStateGame();

	virtual std::shared_ptr<CState> OnUpdate() override;

private:
	std::shared_ptr<CEntity> m_cameraEntity;

	f16	m_rotx_ps = 0.0f;
	f16	m_roty_ps = 0.0f;

	std::shared_ptr<CEntity>	m_crosshairEntity;
	std::shared_ptr<CMesh>		m_crosshairPassiveMesh;
	std::shared_ptr<CMesh>		m_crosshairActiveMesh;

	std::shared_ptr<CEntity>	m_movableEntity;
	std::shared_ptr<CEntity>	m_skyboxEntity;
	std::shared_ptr<CEntity>	m_pulseEntity;

	std::shared_ptr<CText>	m_fpsCurrentText;
	std::shared_ptr<CText>	m_fpsMaxText;
	f16						m_updateFpsTime;

	std::shared_ptr<CText>	m_tracerText;

	f16	m_maxFps = 0.0f;
	Geometry<VertexPC>		m_fpsGraphGeometry;
	std::shared_ptr<CMesh>	m_fpsGraphMesh;
	u32 m_fpsGeometryIndex = 0;

	std::shared_ptr<const CAudioSource> m_backgroundMusic;
};
