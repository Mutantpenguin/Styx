#include "CCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/CWorld.hpp"


CCamera::CCamera( const std::string &name, float zNear, float zFar ) :
	CEntity( name ),
	m_zNear { zNear },
	m_zFar { zFar }
{
}

void CCamera::ZNear( float zNear )
{
	m_zNear = zNear;
}

float CCamera::ZNear( void ) const
{
	return( m_zNear );
}

void CCamera::ZFar( float zFar )
{
	m_zFar = zFar;
}

float CCamera::ZFar( void ) const
{
	return( m_zFar );
}

glm::vec3 const CCamera::Up( void ) const
{
	return( CWorld::Y * Transform.Orientation() );
}

void CCamera::Direction( const glm::vec3 &direction )
{
	const glm::mat4 RotationMatrix = glm::lookAt( Transform.Position(), Transform.Position() + direction, CWorld::Y );

	Transform.Orientation( glm::toQuat( RotationMatrix ) );
}

const glm::vec3 CCamera::Direction( void ) const
{
	return( CWorld::Z * Transform.Orientation() );
}

const CFrustum CCamera::Frustum( void ) const
{
	return( CFrustum( ViewProjectionMatrix() ) );
}

const glm::mat4 CCamera::ViewProjectionMatrix( void ) const
{
	return( ProjectionMatrix() * Transform.ViewMatrix() );
}
