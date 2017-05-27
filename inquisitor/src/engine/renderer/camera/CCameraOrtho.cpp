#include "CCameraOrtho.hpp"

#include <glm/gtc/matrix_transform.hpp>

CCameraOrtho::CCameraOrtho( const CSettings &settings, float zNear, float zFar ) :
	CCamera( zNear, zFar ),
	m_screenWidth { settings.renderer.window.size.width },
	m_screenHeight { settings.renderer.window.size.height }
{
}

CCameraOrtho::~CCameraOrtho()
{
}

const glm::mat4 CCameraOrtho::CalculateProjectionMatrix(void) const
{
	return( glm::ortho( 0.0f, static_cast< float >( m_screenWidth ), 0.0f, static_cast< float >( m_screenHeight ), m_zNear, m_zFar ) );
}
