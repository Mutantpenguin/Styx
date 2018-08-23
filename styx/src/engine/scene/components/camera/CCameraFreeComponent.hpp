#ifndef CCAMERAFREECOMPONENT_HPP
#define CCAMERAFREECOMPONENT_HPP

#include "src/engine/scene/components/camera/CCameraComponent.hpp"

class CCameraFreeComponent final : public CCameraComponent
{
private:
	CCameraFreeComponent(const CCameraFreeComponent& rhs);
	CCameraFreeComponent& operator=(const CCameraFreeComponent& rhs);

public:
	CCameraFreeComponent( const std::shared_ptr< CEntity > &parent, float aspectRatio, float fov, float zNear, float zFar );
	~CCameraFreeComponent() {};

	void FOV( float fov );
	[[nodiscard]] float FOV( void ) const;

	void	MoveForward( const float distance );
	void	MoveBackward( const float distance );
	void	MoveUp( const float distance );
	void	MoveDown( const float distance );
	void	MoveLeft( const float distance );
	void	MoveRight( const float distance );

	void Rotate( const float pitchAngle, const float yawAngle );

	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix( void ) const override;

private:
	const float	m_aspectRatio;

	float	m_fov;
};

#endif // CCAMERAFREECOMPONENT_HPP
