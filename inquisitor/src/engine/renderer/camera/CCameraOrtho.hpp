#ifndef CCAMERAORTHO_HPP
#define CCAMERAORTHO_HPP

#include "src/engine/system/CSettings.hpp"

#include "src/engine/renderer/camera/CCamera.hpp"

class CCameraOrtho : public CCamera
{
private:
	CCameraOrtho( const CCameraOrtho& rhs );
	CCameraOrtho& operator=( const CCameraOrtho& rhs );

public:
	CCameraOrtho( const CSettings &settings, float zNear, float zFar );
	~CCameraOrtho();

public:
	virtual const glm::mat4 CalculateProjectionMatrix( void ) const override;

private:
	const std::uint32_t m_screenWidth;
	const std::uint32_t m_screenHeight;
};

#endif // CCAMERAORTHO_HPP
