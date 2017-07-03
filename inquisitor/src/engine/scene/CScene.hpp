#ifndef CSCENE_HPP
#define CSCENE_HPP

#include <vector>

#include "src/engine/helper/CColor.hpp"

#include "src/engine/renderer/camera/CCamera.hpp"

#include "src/engine/scene/CEntity.hpp"

class CScene
{
public:
	CScene();
	~CScene();

	void AddEntity( const std::shared_ptr< const CEntity > &entity );
	void RemoveEntity( const std::shared_ptr< const CEntity > &entity );

	const std::vector< const CMesh * > &Meshes( void ) const;

	[[nodiscard]] const std::shared_ptr< const CCamera > &Camera( void ) const;
	void Camera( const std::shared_ptr< const CCamera > &camera );

	[[nodiscard]] const CColor &ClearColor( void ) const;
	void ClearColor( const CColor &clearColor );

private:
	std::vector< std::shared_ptr< const CEntity > > m_entities;

	std::shared_ptr< const CCamera > m_camera;

	CColor m_clearColor { 0.0f, 0.0f, 0.0f, 0.0f };
};

#endif // CSCENE_HPP
