#ifndef CSCENE_HPP
#define CSCENE_HPP

#include <vector>
#include <set>

#include "src/engine/helper/CColor.hpp"

#include "src/engine/scene/CEntity.hpp"

#include "src/engine/scene/components/camera/CCameraComponent.hpp"

class CScene
{
public:
	struct MeshInstance
	{
		const CMesh * mesh;
		CTransform Transform;
		float viewDepth;
	};

	using TMeshes = std::vector< MeshInstance >;

public:
	CScene();
	~CScene();

	[[nodiscard]] std::shared_ptr< CEntity > CreateEntity( const std::string &name );
	void DeleteEntity( const std::shared_ptr< const CEntity > &entity );

	[[nodiscard]] const std::shared_ptr< const CEntity > &Camera( void ) const;
	void Camera( const std::shared_ptr< const CEntity > &cameraEntity );

	[[nodiscard]] const TMeshes &Meshes( void ) const;

	[[nodiscard]] const CColor &ClearColor( void ) const;
	void ClearColor( const CColor &clearColor );

	template<typename... T_Components>
	std::vector<std::shared_ptr<const CEntity>> GetEntitiesWithComponents()
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
	void Each( std::function<void( const std::shared_ptr<const CEntity>& )> lambda )
	{
		for( const auto &entity : m_entities )
		{
			if( entity->HasComponents<T_Components...>() )
			{
				lambda( entity );
			}
		}
	};

private:
	std::set< std::shared_ptr< const CEntity > > m_entities;

	std::shared_ptr< const CEntity > m_cameraEntity;

	CColor m_clearColor { 0.0f, 0.0f, 0.0f, 0.0f };

	const std::uint16_t m_id = ++s_lastId;

	static std::uint16_t s_lastId;
};

#endif // CSCENE_HPP
