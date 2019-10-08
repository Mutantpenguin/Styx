#include "src/scene/CTransform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/scene/CWorld.hpp"

void CTransform::Direction( const glm::vec3 &direction )
{
	const glm::mat4 RotationMatrix = glm::lookAt( Position, Position + direction, CWorld::Y );

	Orientation = glm::toQuat( RotationMatrix );
}

const glm::vec3 CTransform::Direction() const
{
	return( CWorld::Z * Orientation );
}

glm::vec3 const CTransform::Up() const
{
	return( CWorld::Y * Orientation );
}

void CTransform::Rotate( const f16 pitchAngle, const f16 yawAngle, const f16 rollAngle )
{
	Orientation = glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( yawAngle ), CWorld::Y ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( rollAngle ), CWorld::Z ) * Orientation;
}

const glm::mat4 CTransform::ViewMatrix() const
{
	return( glm::translate( glm::toMat4( Orientation ), -Position ) );
}

const glm::mat4 CTransform::ModelMatrix() const
{
	glm::mat4 modelMatrix = glm::mat4( 1.0f );

	modelMatrix = glm::translate( modelMatrix, Position );

	modelMatrix = modelMatrix * glm::toMat4( Orientation );

	modelMatrix = glm::scale( modelMatrix, Scale );

	return( modelMatrix );
}