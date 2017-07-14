#ifndef CSCENE_HPP
#define CSCENE_HPP

#include <vector>
#include <set>

#include "src/engine/helper/CColor.hpp"

#include "src/engine/scene/CEntity.hpp"

#include "src/engine/scene/components/CTransformComponent.hpp"

#include "src/engine/scene/camera/CCamera.hpp"

class CScene
{
public:
	struct MeshInstance
	{
		const CMesh * mesh;
		CTransformComponent Transform;
	};

	using TMeshes = std::vector< MeshInstance >;

public:
	CScene();
	~CScene();

	void AddEntity( const std::shared_ptr< const CEntity > &entity );
	void RemoveEntity( const std::shared_ptr< const CEntity > &entity );

	const TMeshes &Meshes( void ) const;

	[[nodiscard]] const std::shared_ptr< const CCamera > &Camera( void ) const;
	void Camera( const std::shared_ptr< const CCamera > &camera );

	[[nodiscard]] const CColor &ClearColor( void ) const;
	void ClearColor( const CColor &clearColor );

private:
	std::set< std::shared_ptr< const CEntity > > m_entities;

	std::shared_ptr< const CCamera > m_camera;

	CColor m_clearColor { 0.0f, 0.0f, 0.0f, 0.0f };
};

#endif // CSCENE_HPP
