#include "src/engine/scene/components/CTransformComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/scene/CWorld.hpp"

void CTransformComponent::Position( const glm::vec3 &position )
{
	m_position = position;
}

const glm::vec3 &CTransformComponent::Position( void ) const
{
	return( m_position );
}

void CTransformComponent::Orientation( const glm::quat &orientation )
{
	m_orientation = orientation;
}

const glm::quat &CTransformComponent::Orientation( void ) const
{
	return( m_orientation );
}

void CTransformComponent::Direction( const glm::vec3 &direction )
{
	const glm::mat4 RotationMatrix = glm::lookAt( m_position, m_position + direction, CWorld::Y );

	m_orientation = glm::toQuat( RotationMatrix );
}

glm::vec3 const CTransformComponent::Direction( void ) const
{
	return( CWorld::Z * m_orientation );
}

const glm::mat4 CTransformComponent::ViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( m_orientation ), -m_position ) );
}
