#include "CScene.hpp"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::AddMesh( const std::shared_ptr< const CMesh > &mesh )
{
	m_meshes.push_back( mesh );
}

void CScene::RemoveMesh( const std::shared_ptr< const CMesh > &mesh )
{
	m_meshes.remove( mesh );
}

const std::list< std::shared_ptr< const CMesh > > &CScene::Meshes( void ) const
{
	return( m_meshes );
}

const std::shared_ptr< const CCamera > &CScene::Camera( void ) const
{
	return( m_camera );
}

void CScene::Camera( const std::shared_ptr< const CCamera > &camera )
{
	m_camera = camera;
}
