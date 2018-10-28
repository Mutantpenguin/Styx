#include "CCameraComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/scene/CWorld.hpp"


CCameraComponent::CCameraComponent( const std::shared_ptr< CEntity > &parent, float zNear, float zFar ) :
	CBaseComponent( parent ),
	m_zNear { zNear },
	m_zFar { zFar }
{
}

void CCameraComponent::ZNear( float zNear )
{
	m_zNear = zNear;
}

float CCameraComponent::ZNear() const
{
	return( m_zNear );
}

void CCameraComponent::ZFar( float zFar )
{
	m_zFar = zFar;
}

float CCameraComponent::ZFar() const
{
	return( m_zFar );
}

const CFrustum CCameraComponent::Frustum() const
{
	return( CFrustum( ViewProjectionMatrix() ) );
}

const glm::mat4 CCameraComponent::ViewProjectionMatrix() const
{
	return( ProjectionMatrix() * m_parent->Transform.ViewMatrix() );
}
