#include "CCameraFree.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

CCameraFree::CCameraFree( float aspectRatio, float fov, float zNear, float zFar ) :
	CCamera( aspectRatio, fov, zNear, zFar )
{
}

CCameraFree::~CCameraFree()
{
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
	m_position += worldY * distance;
}

void CCameraFree::MoveDown( const float distance )
{
	m_position -= worldY * distance;
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
	m_orientation = glm::angleAxis( glm::radians( pitchAngle ), worldX ) * m_orientation * glm::angleAxis( glm::radians( yawAngle ), worldY );
}
