#ifndef CCAMERA_HPP
#define CCAMERA_HPP

#include <glm/gtc/quaternion.hpp>

#include "src/engine/renderer/CMesh.hpp"
#include "src/engine/renderer/CFrustum.hpp"

#include "../../helper/CSize.hpp"

class CCamera
{
public:
	void	SetFOV( float fov );
	void	SetZNear( float zNear );
	void	SetZFar( float zFar );

	void	SetPosition( const glm::vec3 &position );

	float	FOV( void ) const;
	float	ZNear( void ) const;
	float	ZFar( void ) const;

	glm::vec3	const  &Position( void ) const;
	glm::vec3	const  Direction( void ) const;
	glm::vec3	const  Up( void ) const;

	const CFrustum &CalculateFrustum( void );

	const glm::mat4 CalculateProjectionMatrix( void ) const;
	const glm::mat4 CalculateViewMatrix( void ) const;
	const glm::mat4 CalculateViewProjectionMatrix( void ) const;

protected:
	CCamera( float aspectRatio, float fov, float zNear, float zFar );

	glm::vec3 m_position	{ 0, 0, 0 };
	glm::quat m_orientation	{ 1, 0, 0, 0 };

	const glm::vec3 worldZ	{ 0.0f, 0.0f, 1.0f };
	const glm::vec3 worldY	{ 0.0f, 1.0f, 0.0f };
	const glm::vec3 worldX	{ 1.0f, 0.0f, 0.0f };

private:
	const float	m_aspectRatio;

	float	m_fov;
	float	m_zNear;
	float	m_zFar;

	CFrustum m_frustum;
};

#endif // CCAMERA_HPP
