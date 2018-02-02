#include "CScene.hpp"

#include <glm/gtx/norm.hpp>

#include "src/ext/minitrace/minitrace.h"

#include "src/engine/logger/CLogger.hpp"

std::uint16_t CScene::s_lastId = 0;

CScene::CScene()
{
}

CScene::~CScene()
{
}

std::shared_ptr< CEntity > CScene::CreateEntity( const std::string &name )
{
	auto entity = std::make_shared< CEntity >( name, m_id );

	m_entities.insert( entity );

	return( entity );
}

void CScene::DeleteEntity( const std::shared_ptr< const CEntity > &entity )
{
	// TODO only erase, when the are no shared_ptr pointing to it?
	m_entities.erase( entity );
}

const std::shared_ptr< const CEntity > &CScene::Camera( void ) const
{
	return( m_cameraEntity );
}

void CScene::Camera( const std::shared_ptr< const CEntity > &cameraEntity )
{
	if( !cameraEntity->HasComponents<CCameraComponent>() )
	{
		logWARNING( "entity '{0}' with id '{1}' has no CCameraComponent", cameraEntity->Name(), cameraEntity->Id );
		return;
	}

	if( cameraEntity->m_sceneId != m_id )
	{
		logWARNING( "camera '{0}' with id '{1}' does not belong to this scene", cameraEntity->Name(), cameraEntity->Id );
		return;
	}

	m_cameraEntity = cameraEntity;
}

const CColor &CScene::ClearColor( void ) const
{
	return( m_clearColor );
}

void CScene::ClearColor( const CColor &clearColor )
{
	m_clearColor = clearColor;
}
