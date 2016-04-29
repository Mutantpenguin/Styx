#ifndef CSTATEGAME_HPP
#define CSTATEGAME_HPP

#include "CState.hpp"

class CStateGame final : public CState
{
public:
	CStateGame( const CFileSystem &filesystem, const CSettings &settings, std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer );
	~CStateGame();

	virtual std::shared_ptr< CState > Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input ) override;

private:
	std::shared_ptr< CCamera > m_camera;

	float	m_xrot = 0.0f;
	float	m_yrot = 0.0f;
	float	m_rotx_ps = 0.0f;
	float	m_roty_ps = 0.0f;

	std::shared_ptr< CMesh >	mesh;
	std::shared_ptr< CMesh >	mesh2;
	std::shared_ptr< CMesh >	skyboxMesh;
};

#endif // CSTATEGAME_HPP
