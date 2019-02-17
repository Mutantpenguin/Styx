#pragma once

#include <memory>

#include "src/scene/CEntity.hpp"

class CBaseComponent
{
public:
	// TODO is the parent really needed?
	// only place which needs this right now are the cameras, and I am sure, the movement controller shouldn't even be in there...
	CBaseComponent( const std::shared_ptr< CEntity > &parent ) :
		m_parent { parent }
	{};

	virtual ~CBaseComponent()
	{};

protected:
	const std::shared_ptr< CEntity > m_parent;
};
