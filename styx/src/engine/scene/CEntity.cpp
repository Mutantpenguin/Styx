#include "CEntity.hpp"

u32 CEntity::s_lastId = 0;

CEntity::CEntity( const std::string &name, const u16 sceneId ) :
	m_name{ name },
	m_sceneId { sceneId }
{
	logDEBUG( "creating entity '{0}' with id '{1}'", m_name, Id );
}

CEntity::~CEntity()
{
}

const std::string &CEntity::Name( void ) const
{
	return( m_name );
}
