#ifndef CSCENE_HPP
#define CSCENE_HPP

#include <list>

#include "src/engine/renderer/camera/CCamera.hpp"
#include "src/engine/renderer/mesh/CMesh.hpp"

class CScene
{
public:
	CScene();
	~CScene();

	void AddMesh( const std::shared_ptr< const CMesh > &mesh );
	void RemoveMesh( const std::shared_ptr< const CMesh > &mesh );

	const std::list< std::shared_ptr< const CMesh > > &Meshes( void ) const;

	const std::shared_ptr< CCamera > &Camera( void ) const;
	void Camera( const std::shared_ptr< CCamera > &camera );

private:
	std::list< std::shared_ptr< const CMesh > > m_meshes;

	std::shared_ptr< CCamera > m_camera;
};

#endif // CSCENE_HPP
