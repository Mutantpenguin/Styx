#ifndef CCAMERA_HPP
#define CCAMERA_HPP

#include "CMesh.hpp"
#include "CFrustum.hpp"

#include "../helper/CSize.hpp"

class CCamera final
{
public:
	CCamera( float aspectRatio, float fov, float zNear, float zFar, const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up );

	void	Update( void );

	void	SetFOV( float fov );
	void	SetZNear( float zNear );
	void	SetZFar( float zFar );

	void	SetPosition( const glm::vec3 &position );
	void	SetDirection( const glm::vec3 &direction );
	void	SetUp( const glm::vec3 &up );

	void	MoveForward( const float distance );
	void	MoveBackward( const float distance );
	void	MoveUp( const float distance );
	void	MoveDown( const float distance );
	void	MoveLeft( const float distance );
	void	MoveRight( const float distance );

	void	LookAt( const glm::vec3 &position );

	float	FOV( void ) const;
	float	ZNear( void ) const;
	float	ZFar( void ) const;

	glm::vec3	const  &Position( void ) const;
	glm::vec3	const  &Direction( void ) const;
	glm::vec3	const  &Up( void ) const;

	const CFrustum &Frustum( void ) const;

	const glm::mat4 &ProjectionMatrix( void ) const;
	const glm::mat4 &ViewMatrix( void ) const;
	const glm::mat4 &ViewProjectionMatrix( void ) const;

private:
	glm::vec3	m_position;
	glm::vec3	m_direction;
	glm::vec3	m_up;

	float	m_aspectRatio;

	float	m_fov;
	float	m_zNear;
	float	m_zFar;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_viewProjectionMatrix;

	CFrustum m_frustum;
};

#endif // CCAMERA_HPP
