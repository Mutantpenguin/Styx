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

const std::vector< const CMesh * > &CScene::Meshes( void ) const
{
	static std::vector< const CMesh * > meshes( 5000 );
	meshes.clear();

	const auto &frustum = m_camera->CalculateFrustum();

	for( const auto &entity : m_entities )
	{
		const auto &mesh = entity->Mesh().get();

		if( mesh )
		{
			if( frustum.IsSphereInside( mesh->Position(), mesh->BoundingSphereRadius() ) )
			{
				meshes.push_back( mesh );
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
