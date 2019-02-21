#pragma once

#include <glm/gtc/quaternion.hpp>

#include "src/helper/Types.hpp"

#include "src/scene/components/CBaseComponent.hpp"

#include "src/scene/CFrustum.hpp"

#include "src/helper/CSize.hpp"

class CCameraComponent : public CBaseComponent
{
public:
	CCameraComponent( const std::shared_ptr< CEntity > &parent, const f16 zNear, const f16 zFar );
	virtual ~CCameraComponent() {};

	static const u16 Index = static_cast<u16>( EComponentIndex::CAMERA );

	void	ZNear( const f16 zNear );
	[[nodiscard]] f16 ZNear() const;

	void	ZFar( const f16 zFar );
	[[nodiscard]] f16 ZFar() const;

	[[nodiscard]] const CFrustum Frustum() const;

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix() const = 0;
	[[nodiscard]] const glm::mat4 ViewProjectionMatrix() const;

protected:
	f16	m_zNear;
	f16	m_zFar;
};
