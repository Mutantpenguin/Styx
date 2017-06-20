#ifndef CSCENE_HPP
#define CSCENE_HPP

#include <list>

#include "src/engine/helper/CColor.hpp"

#include "src/engine/renderer/camera/CCamera.hpp"
#include "src/engine/renderer/model/CMesh.hpp"

class CScene
{
public:
	CScene();
	~CScene();

	void AddMesh( const std::shared_ptr< const CMesh > &mesh );
	void RemoveMesh( const std::shared_ptr< const CMesh > &mesh );

	const std::list< std::shared_ptr< const CMesh > > &Meshes( void ) const;

	[[nodiscard]] const std::shared_ptr< const CCamera > &Camera( void ) const;
	void Camera( const std::shared_ptr< const CCamera > &camera );

	[[nodiscard]] const CColor &ClearColor( void ) const;
	void ClearColor( const CColor &clearColor );

private:
	std::list< std::shared_ptr< const CMesh > > m_meshes;

	std::shared_ptr< const CCamera > m_camera;

	CColor m_clearColor { 0.0f, 0.0f, 0.0f, 0.0f };
};

#endif // CSCENE_HPP
