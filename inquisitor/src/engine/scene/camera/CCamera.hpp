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

	void	ZNear( float zNear );
	[[nodiscard]] float	ZNear( void ) const;

	void	ZFar( float zFar );
	[[nodiscard]]float	ZFar( void ) const;

	[[nodiscard]] glm::vec3 const Up( void ) const;

	void Direction( const glm::vec3 &direction );
	[[nodiscard]] const glm::vec3 Direction( void ) const;

	[[nodiscard]] const CFrustum Frustum( void ) const;

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix( void ) const = 0;
	[[nodiscard]] const glm::mat4 ViewProjectionMatrix( void ) const;

protected:
	float	m_zNear;
	float	m_zFar;
};

#endif // CCAMERA_HPP
