#include "src/engine/scene/CTransform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/scene/CWorld.hpp"

void CTransform::Position( const glm::vec3 &position )
{
	m_position = position;
}

const glm::vec3 &CTransform::Position( void ) const
{
	return( m_position );
}

void CTransform::Orientation( const glm::quat &orientation )
{
	m_orientation = orientation;
}

void CTransform::Scale( const glm::vec3 &scale )
{
	m_scale = scale;
}

const glm::vec3 &CTransform::Scale( void ) const
{
	return( m_scale );
}

const glm::quat &CTransform::Orientation( void ) const
{
	return( m_orientation );
}

void CTransform::Direction( const glm::vec3 &direction )
{
	const glm::mat4 RotationMatrix = glm::lookAt( m_position, m_position + direction, CWorld::Y );

	m_orientation = glm::toQuat( RotationMatrix );
}

const glm::vec3 CTransform::Direction( void ) const
{
	return( CWorld::Z * m_orientation );
}

glm::vec3 const CTransform::Up( void ) const
{
	return( CWorld::Y * m_orientation );
}

void CTransform::Rotate( const float pitchAngle, const float yawAngle, const float rollAngle )
{
	m_orientation = glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * m_orientation;
	m_orientation = glm::angleAxis( glm::radians( yawAngle ), CWorld::Y ) * m_orientation;
	m_orientation = glm::angleAxis( glm::radians( rollAngle ), CWorld::Z ) * m_orientation;
}

const glm::mat4 CTransform::ViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( m_orientation ), -m_position ) );
}
