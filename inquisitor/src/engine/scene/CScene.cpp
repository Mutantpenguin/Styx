#include "CScene.hpp"

#include <glm/gtx/norm.hpp>

#include "src/ext/minitrace/minitrace.h"

#include "src/engine/logger/CLogger.hpp"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::AddEntity( const std::shared_ptr< const CEntity > &entity )
{
	m_entities.insert( entity );
}

void CScene::RemoveEntity( const std::shared_ptr< const CEntity > &entity )
{
	m_entities.erase( entity );
}

const CScene::TMeshes &CScene::Meshes( void ) const
{
	MTR_SCOPE( "scene", "collect visible meshes" );

	static CScene::TMeshes meshes;
	meshes.clear();

	const auto &frustum = m_camera->Frustum();

	for( const auto &entity : m_entities )
	{
		const auto &mesh = entity->Mesh().get();

		if( mesh )
		{
			// TODO implement Octree here
			if( frustum.IsSphereInside( entity->Transform.Position(), glm::length( mesh->BoundingSphereRadiusVector() * entity->Transform.Scale() ) ) )
			{
				meshes.push_back( { mesh, entity->Transform, glm::length2( entity->Transform.Position() - m_camera->Transform.Position() ) } );
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
	const auto it = std::find( std::cbegin( m_entities ), std::cend( m_entities ), camera );
	if( it == std::cend( m_entities ) )
	{
		logERROR( "camera '{0}' does not belong to this scene", camera->Name() );
	}
	else
	{
		m_camera = camera;
	}
}

const CColor &CScene::ClearColor( void ) const
{
	return( m_clearColor );
}

void CScene::ClearColor( const CColor &clearColor )
{
	m_clearColor = clearColor;
}
