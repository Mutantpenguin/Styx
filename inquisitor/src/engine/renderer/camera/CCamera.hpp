#ifndef CCAMERA_HPP
#define CCAMERA_HPP

#include <glm/gtc/quaternion.hpp>

#include "src/engine/renderer/CFrustum.hpp"

#include "src/engine/helper/CSize.hpp"

class CCamera
{
public:
	CCamera( float zNear, float zFar );

	void	SetZNear( float zNear );
	void	SetZFar( float zFar );

	void	SetPosition( const glm::vec3 &position );
	void	SetDirection( const glm::vec3 &direction );

	float	ZNear( void ) const;
	float	ZFar( void ) const;

	glm::vec3	const  &Position( void ) const;
	glm::vec3	const  Direction( void ) const;
	glm::vec3	const  Up( void ) const;

	const CFrustum CalculateFrustum( void ) const;

	virtual const glm::mat4 CalculateProjectionMatrix( void ) const = 0;
	const glm::mat4 CalculateViewMatrix( void ) const;
	const glm::mat4 CalculateViewProjectionMatrix( void ) const;

protected:
	glm::vec3 m_position	{ 0.0f, 0.0f, 0.0f };
	glm::quat m_orientation	{ 1.0f, 0.0f, 0.0f, 0.0f };

	float	m_zNear;
	float	m_zFar;
};

#endif // CCAMERA_HPP
