#include "CCameraFree.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/scene/CWorld.hpp"

CCameraFree::CCameraFree( float aspectRatio, float fov, float zNear, float zFar ) :
	CCamera( zNear, zFar ),
	m_aspectRatio { aspectRatio },
	m_fov { fov }
{
}

CCameraFree::~CCameraFree()
{
}

void CCameraFree::SetFOV( float fov )
{
	if( fov > 155 )
	{
		m_fov = 155;
	}
	else if( fov < 25 )
	{
		m_fov = 25;
	}
	else
	{
		m_fov = fov;
	}
}

float CCameraFree::FOV( void ) const
{
	return( m_fov );
}

void CCameraFree::MoveForward( const float distance )
{
	m_position -= Direction() * distance;
}

void CCameraFree::MoveBackward( const float distance )
{
	m_position += Direction() * distance;
}

void CCameraFree::MoveUp( const float distance )
{
	m_position += CWorld::Y * distance;
}

void CCameraFree::MoveDown( const float distance )
{
	m_position -= CWorld::Y * distance;
}

void CCameraFree::MoveLeft( const float distance )
{
	m_position -= glm::cross( Up(), Direction() ) * distance;
}

void CCameraFree::MoveRight( const float distance )
{
	m_position += glm::cross( Up(), Direction() ) * distance;
}

void CCameraFree::Rotate( const float pitchAngle, const float yawAngle )
{
	m_orientation = glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * m_orientation * glm::angleAxis( glm::radians( yawAngle ), CWorld::Y );
}

const glm::mat4 CCameraFree::CalculateProjectionMatrix( void ) const
{
	return( glm::perspective( glm::radians( m_fov ), m_aspectRatio, m_zNear, m_zFar ) );
}
