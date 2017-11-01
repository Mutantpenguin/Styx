#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>
#include <memory>

#include "src/engine/scene/components/CTransformComponent.hpp"

#include "src/engine/renderer/model/CMesh.hpp"

using EntityID = std::uint32_t;

class CEntity
{
public:
	CEntity( const std::string &name );
	~CEntity();

	void Mesh( const std::shared_ptr< const CMesh > &mesh );
	const std::shared_ptr< const CMesh > Mesh( void ) const;

	const std::string &Name( void ) const;

	EntityID Id( void ) const;

	CTransformComponent Transform;

private:
	const std::string m_name;

	std::shared_ptr< const CMesh > m_mesh = nullptr;

	const EntityID m_id = ++s_lastId;

	static EntityID s_lastId;
};

#endif // COBJECT_HPP
