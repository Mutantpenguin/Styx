#ifndef CCAMERAFREE_HPP
#define CCAMERAFREE_HPP

#include "CCamera.hpp"

class CCameraFree final : public CCamera
{
private:
	CCameraFree(const CCameraFree& rhs);
	CCameraFree& operator=(const CCameraFree& rhs);

public:
	CCameraFree( float aspectRatio, float fov, float zNear, float zFar );
	~CCameraFree();

	void	SetDirection( const glm::vec3 &direction );

	void	MoveForward( const float distance );
	void	MoveBackward( const float distance );
	void	MoveUp( const float distance );
	void	MoveDown( const float distance );
	void	MoveLeft( const float distance );
	void	MoveRight( const float distance );

	void	Rotate( const float pitchAngle, const float yawAngle );
};

#endif // CCAMERAFREE_HPP
