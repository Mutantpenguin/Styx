#ifndef CTRANSFORMSYSTEM_HPP
#define CTRANSFORMSYSTEM_HPP

#include "ccomponentsystem.hpp"

#include "components/transformcomponent.hpp"

class CTransformSystem : public CComponentSystem<TransformComponent>
{
public:
	static SystemID systemID;

	glm::vec3 GetPosition( EntityID id ) const;
	void SetPosition( EntityID id, glm::vec3 pos );

	void Update( const double );
};

#endif // CTRANSFORMSYSTEM_HPP
