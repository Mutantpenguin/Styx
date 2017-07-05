#include "CScene.hpp"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::AddEntity( const std::shared_ptr< const CEntity > &entity )
{
	m_entities.push_back( entity );
}

void CScene::RemoveEntity( const std::shared_ptr< const CEntity > &entity )
{
	m_entities.erase( std::remove( std::begin( m_entities ), std::end( m_entities ), entity ), std::end( m_entities ) );
}

const CScene::TMeshes &CScene::Meshes( void ) const
{
	static CScene::TMeshes meshes;
	meshes.clear();

	const auto &frustum = m_camera->CalculateFrustum();

	for( const auto &entity : m_entities )
	{
		const auto &mesh = entity->Mesh().get();

		if( mesh )
		{
			// TODO implement Octree here
			if( frustum.IsSphereInside( mesh->Position(), mesh->BoundingSphereRadius() ) )
			{
				// TODO tranform
				meshes.push_back( { mesh, { 1.0f, 1.0f, 1.0f } } );
			}
		}
	}

	return( meshes );
}

const std::shared_ptr< const CCamera > &CScene::Camera( void ) const
{
	return( m_camera );
}

void CScene::Camera( const std::shared_ptr< const CCamera > &camera )
{
	m_camera = camera;
}

const CColor &CScene::ClearColor( void ) const
{
	return( m_clearColor );
}

void CScene::ClearColor( const CColor &clearColor )
{
	m_clearColor = clearColor;
}
