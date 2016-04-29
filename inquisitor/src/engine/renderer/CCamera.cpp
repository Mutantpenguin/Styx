#include "CCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "../logger/CLogger.hpp"


CCamera::CCamera( float aspectRatio, float fov, float zNear, float zFar, const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up ) :
	m_position { position },
	m_direction { direction },
	m_up { up },
	m_aspectRatio { aspectRatio },
	m_fov { fov },
	m_zNear { zNear },
	m_zFar { zFar }
{
}

void CCamera::Update( void )
{
	/*
	 * calculate every needed matrix just once
	 */
	m_projectionMatrix		= glm::perspective( m_fov, m_aspectRatio, m_zNear, m_zFar );
	m_viewMatrix			= glm::lookAt( m_position, m_position + m_direction, m_up );
	m_viewProjectionMatrix	= m_projectionMatrix * m_viewMatrix;

	/*
	 * frustum
	 */
	m_frustum.Update( m_viewProjectionMatrix );
}

void CCamera::MoveForward( const float distance )
{
	m_position += m_direction * distance;
}

void CCamera::MoveBackward( const float distance )
{
	m_position += m_direction * -distance;
}

void CCamera::MoveUp( const float distance )
{
	m_position += m_up * distance;
}

void CCamera::MoveDown( const float distance )
{
	m_position += m_up * -distance;
}

void CCamera::MoveLeft( const float distance )
{
	m_position += glm::cross( m_up, m_direction ) * distance;
}

void CCamera::MoveRight( const float distance )
{
	m_position += glm::cross( m_up, m_direction ) * -distance;
}

void CCamera::SetFOV( float fov )
{
	m_fov = fov;
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
	m_direction = direction;
}

void CCamera::SetUp( const glm::vec3 &up )
{
	m_up = up;
}

void CCamera::LookAt( const glm::vec3 &position )
{
	SetDirection( glm::normalize( position - m_position ) );
}

float CCamera::FOV( void ) const
{
	return( m_fov );
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

glm::vec3 const &CCamera::Direction( void ) const
{
	return( m_direction );
}

glm::vec3 const &CCamera::Up( void ) const
{
	return( m_up );
}

const CFrustum &CCamera::Frustum( void ) const
{
	return( m_frustum );
}

const glm::mat4 &CCamera::ProjectionMatrix( void ) const
{
	return( m_projectionMatrix );
}

const glm::mat4 &CCamera::ViewMatrix( void ) const
{
	return( m_viewMatrix );
}

const glm::mat4 &CCamera::ViewProjectionMatrix( void ) const
{
	return( m_viewProjectionMatrix );
}
