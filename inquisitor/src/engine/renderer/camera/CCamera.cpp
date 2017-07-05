#include "CCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/CWorld.hpp"


CCamera::CCamera( float zNear, float zFar ) :
	m_zNear { zNear },
	m_zFar { zFar }
{
}

void CCamera::SetZNear( float zNear )
{
	m_zNear = zNear;
}

void CCamera::SetZFar( float zFar )
{
	m_zFar = zFar;
}

void CCamera::SetPosition( const glm::vec3 &position )
{
	m_position = position;
}

void CCamera::SetDirection( const glm::vec3 &direction )
{
	const glm::mat4 RotationMatrix = glm::lookAt( m_position, m_position + direction, CWorld::Y );

	m_orientation = glm::toQuat( RotationMatrix );
}

float CCamera::ZNear( void ) const
{
	return( m_zNear );
}

float CCamera::ZFar( void ) const
{
	return( m_zFar );
}

glm::vec3 const &CCamera::Position( void ) const
{
	return( m_position );
}

glm::vec3 const CCamera::Direction( void ) const
{
	return( CWorld::Z * m_orientation );
}

glm::vec3 const CCamera::Up( void ) const
{
	return( CWorld::Y * m_orientation );
}

const CFrustum CCamera::CalculateFrustum( void ) const
{
	return( CFrustum( CalculateViewProjectionMatrix() ) );
}

const glm::mat4 CCamera::CalculateViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( m_orientation ), -m_position ) );
}

const glm::mat4 CCamera::CalculateViewProjectionMatrix( void ) const
{
	return( CalculateProjectionMatrix() * CalculateViewMatrix() );
}
