#include "CScene.hpp"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::AddMesh( std::shared_ptr< CMesh > mesh )
{
	m_meshes.push_back( mesh );
}

void CScene::RemoveMesh( std::shared_ptr< CMesh > mesh )
{
	m_meshes.remove( mesh );
}

const std::list< std::shared_ptr< CMesh > > &CScene::Meshes( void ) const
{
	return( m_meshes );
}

const std::shared_ptr< CCamera > CScene::Camera( void ) const
{
	return( m_camera );
}

void CScene::Camera( std::shared_ptr< CCamera > camera )
{
	m_camera = camera;
}
