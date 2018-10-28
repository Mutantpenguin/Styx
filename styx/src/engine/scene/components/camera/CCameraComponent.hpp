#pragma once

#include <glm/gtc/quaternion.hpp>

#include "src/engine/helper/Types.hpp"

#include "src/engine/scene/components/CBaseComponent.hpp"

#include "src/engine/scene/CFrustum.hpp"

#include "src/engine/helper/CSize.hpp"

class CCameraComponent : public CBaseComponent
{
public:
	CCameraComponent( const std::shared_ptr< CEntity > &parent, float zNear, float zFar );
	virtual ~CCameraComponent() {};

	static const u16 Index = static_cast<u16>( EComponentIndex::CAMERA );

	void	ZNear( float zNear );
	[[nodiscard]] float	ZNear() const;

	void	ZFar( float zFar );
	[[nodiscard]]float	ZFar() const;

	[[nodiscard]] const CFrustum Frustum() const;

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix() const = 0;
	[[nodiscard]] const glm::mat4 ViewProjectionMatrix() const;

protected:
	float	m_zNear;
	float	m_zFar;
};
