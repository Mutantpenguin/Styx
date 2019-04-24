#pragma once

#include "src/core/Types.hpp"

#include "src/scene/components/camera/CCameraComponent.hpp"

class CCameraFreeComponent final : public CCameraComponent
{
private:
	CCameraFreeComponent(const CCameraFreeComponent& rhs);
	CCameraFreeComponent& operator=(const CCameraFreeComponent& rhs);

public:
	CCameraFreeComponent( const std::shared_ptr< CEntity > &parent, const f16 aspectRatio, const f16 fov, const f16 zNear, const f16 zFar );
	~CCameraFreeComponent() {};

	void FOV( const f16 fov );
	[[nodiscard]] f16 FOV() const;

	void	MoveForward( const f16 distance );
	void	MoveBackward( const f16 distance );
	void	MoveUp( const f16 distance );
	void	MoveDown( const f16 distance );
	void	MoveLeft( const f16 distance );
	void	MoveRight( const f16 distance );

	void Rotate( const f16 pitchAngle, const f16 yawAngle );

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix() const override;

private:
	const f16	m_aspectRatio;

	f16	m_fov;
};
