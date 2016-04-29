#include "centity.hpp"

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/lexical_cast.hpp>

#include "components/cbasecomponent.hpp"


CEntity::CEntity()
{

}

CEntity::~CEntity()
{
	m_uuid = boost::lexical_cast<std::string>( boost::uuids::random_generator()() );
}
