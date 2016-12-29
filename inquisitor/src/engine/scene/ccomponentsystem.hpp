#ifndef CCOMPONENTSYSTEM_HPP
#define CCOMPONENTSYSTEM_HPP

#include <unordered_map>

#include "centity.hpp"
#include "csystem.hpp"

using SystemID = std::uint32_t ;

template <typename T>
class CComponentSystem : public CSystem
{
public:
	virtual void Update( const double dt ) = 0;

protected:
	std::unordered_map<EntityID, T*> m_components;
};

#endif // CCOMPONENTSYSTEM_HPP
