#ifndef CCAMERA_HPP
#define CCAMERA_HPP

#include <glm/gtc/quaternion.hpp>

#include "src/engine/scene/CEntity.hpp"

#include "src/engine/scene/CFrustum.hpp"

#include "src/engine/helper/CSize.hpp"

class CCamera : public CEntity
{
public:
	CCamera( const std::string &name, float zNear, float zFar );

	void	SetZNear( float zNear );
	void	SetZFar( float zFar );

	float	ZNear( void ) const;
	float	ZFar( void ) const;

	glm::vec3	const  Up( void ) const;

	const CFrustum Frustum( void ) const;

	virtual const glm::mat4 ProjectionMatrix( void ) const = 0;
	const glm::mat4 ViewProjectionMatrix( void ) const;

protected:
	float	m_zNear;
	float	m_zFar;
};

#endif // CCAMERA_HPP
