#include "CEntity.hpp"

#include "src/engine/logger/CLogger.hpp"

std::uint32_t CEntity::s_lastId = 0;

CEntity::CEntity( const std::string &name, const std::uint16_t sceneId ) :
	m_name{ name },
	m_sceneId { sceneId }
{
	logDEBUG( "creating entity '{0}' with id '{1}'", m_name, Id );
}

CEntity::~CEntity()
{
}

void CEntity::Mesh( const std::shared_ptr< const CMesh > &mesh )
{
	m_mesh = mesh;
}

const std::shared_ptr< const CMesh > CEntity::Mesh( void ) const
{
	return( m_mesh );
}

const std::string &CEntity::Name( void ) const
{
	return( m_name );
}
