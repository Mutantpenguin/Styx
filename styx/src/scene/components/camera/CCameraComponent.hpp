#pragma once

#include <glm/gtc/quaternion.hpp>

#include "src/core/Types.hpp"

#include "src/scene/components/CBaseComponent.hpp"

#include "src/scene/CFrustum.hpp"

#include "src/helper/CSize.hpp"

class CCameraComponent : public CBaseComponent
{
public:
	CCameraComponent( const std::shared_ptr<CEntity> &parent, const f16 zNear, const f16 zFar );
	virtual ~CCameraComponent() {};

	static const u16 Index = static_cast<u16>( EComponentIndex::CAMERA );

	f16	ZNear;
	f16	ZFar;

	[[nodiscard]] const CFrustum Frustum() const;

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix() const = 0;
	[[nodiscard]] const glm::mat4 ViewMatrix() const;
	[[nodiscard]] const glm::mat4 ViewProjectionMatrix() const;
};
