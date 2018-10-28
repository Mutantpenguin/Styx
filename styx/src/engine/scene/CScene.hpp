#pragma once

#include <vector>
#include <set>
#include <functional>

#include <glm/gtx/norm.hpp>

#include "src/engine/helper/Types.hpp"

#include "src/engine/helper/CColor.hpp"

#include "src/engine/scene/CEntity.hpp"

#include "src/engine/scene/components/camera/CCameraComponent.hpp"

class CScene final
{
public:
	CScene();
	~CScene();

	[[nodiscard]] std::shared_ptr< CEntity > CreateEntity( const std::string &name );
	void DeleteEntity( const std::shared_ptr< const CEntity > &entity );

	[[nodiscard]] const std::shared_ptr< const CEntity > &Camera() const;
	void Camera( const std::shared_ptr< const CEntity > &cameraEntity );

	[[nodiscard]] const CColor &ClearColor() const;
	void ClearColor( const CColor &clearColor );

	template<typename... T_Components>
	std::vector<std::shared_ptr<const CEntity>> GetEntitiesWithComponents() const
	{
		std::vector<std::shared_ptr<const CEntity>> entities;
		entities.reserve( m_entities.size() / 4 );

		for( const auto &entity : m_entities )
		{
			if( entity->HasComponents<T_Components...>() )
			{
				entities.push_back( entity );
			}
		}

		return( entities );
	};

	template<typename... T_Components>
	void Each( std::function<void( const std::shared_ptr<const CEntity>& )> lambda ) const
	{
		for( const auto &entity : m_entities )
		{
			if( entity->HasComponents<T_Components...>() )
			{
				lambda( entity );
			}
		}
	};

	template<typename... T_Components>
	void EachInRadius( const glm::vec3 &position, const float radius, std::function<void( const std::shared_ptr<const CEntity>& )> lambda2 ) const
	{
		const auto radiusSquared = std::pow( radius, 2 );

		Each<T_Components...>( [ &position, &radiusSquared, &lambda2 ] ( const std::shared_ptr<const CEntity> &entity )
		{
			// TODO use OcTree
			if( glm::length2( position - entity->Transform.Position() ) <= radiusSquared )
			{
				lambda2( entity );
			}
		} );
	};

private:
	std::set< std::shared_ptr< const CEntity > > m_entities;

	std::shared_ptr< const CEntity > m_cameraEntity;

	CColor m_clearColor { 0.0f, 0.0f, 0.0f, 0.0f };

	const u16 m_id = ++s_lastId;

	static u16 s_lastId;
};
