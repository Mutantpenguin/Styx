#ifndef CCAMERACOMPONENT_HPP
#define CCAMERACOMPONENT_HPP

#include <glm/gtc/quaternion.hpp>

#include "src/engine/scene/components/CBaseComponent.hpp"

#include "src/engine/scene/CFrustum.hpp"

#include "src/engine/helper/CSize.hpp"

class CCameraComponent : public CBaseComponent
{
public:
	CCameraComponent( const std::shared_ptr< CEntity > &parent, float zNear, float zFar );
	virtual ~CCameraComponent() {};

	static const std::uint16_t Index = static_cast<std::uint16_t>( EComponentIndex::CAMERA );

	void	ZNear( float zNear );
	[[nodiscard]] float	ZNear( void ) const;

	void	ZFar( float zFar );
	[[nodiscard]]float	ZFar( void ) const;

	[[nodiscard]] const CFrustum Frustum( void ) const;

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix( void ) const = 0;
	[[nodiscard]] const glm::mat4 ViewProjectionMatrix( void ) const;

protected:
	float	m_zNear;
	float	m_zFar;
};

#endif // CCAMERACOMPONENT_HPP
