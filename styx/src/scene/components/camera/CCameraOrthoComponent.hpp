#pragma once

#include "src/core/Types.hpp"

#include "src/helper/CSize.hpp"

#include "src/scene/components/camera/CCameraComponent.hpp"

class CCameraOrthoComponent final : public CCameraComponent
{
private:
	CCameraOrthoComponent( const CCameraOrthoComponent& rhs );
	CCameraOrthoComponent& operator=( const CCameraOrthoComponent& rhs );

public:
	CCameraOrthoComponent( const std::shared_ptr< CEntity > &parent, const CSize &size, const f16 zNear, const f16 zFar );
	~CCameraOrthoComponent() {};

public:
	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix() const override;

private:
	const CSize m_size;
};
