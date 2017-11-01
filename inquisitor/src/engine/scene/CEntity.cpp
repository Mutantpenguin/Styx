#include "CEntity.hpp"

#include "src/engine/logger/CLogger.hpp"

EntityID CEntity::s_lastId = 0;

CEntity::CEntity( const std::string &name ) :
	m_name { name }
{
	logDEBUG( "creating entity '{0}' with id '{1}'", m_name, m_id );
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

EntityID CEntity::Id( void ) const
{
	return( m_id );
}
