#ifndef CCAMERAFREE_HPP
#define CCAMERAFREE_HPP

#include "src/engine/scene/camera/CCamera.hpp"

class CCameraFree final : public CCamera
{
private:
	CCameraFree(const CCameraFree& rhs);
	CCameraFree& operator=(const CCameraFree& rhs);

public:
	CCameraFree( const std::string &name, float aspectRatio, float fov, float zNear, float zFar );
	~CCameraFree();

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

#endif // CCAMERAFREE_HPP
