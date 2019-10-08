#include "CCameraComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "src/logger/CLogger.hpp"

#include "src/scene/CWorld.hpp"


CCameraComponent::CCameraComponent( const std::shared_ptr<CEntity> &parent, const f16 zNear, const f16 zFar ) :
	CBaseComponent( parent ),
	ZNear { zNear },
	ZFar { zFar }
{}

const CFrustum CCameraComponent::Frustum() const
{
	return( CFrustum( ViewProjectionMatrix() ) );
}

const glm::mat4 CCameraComponent::ViewMatrix() const
{
	return( m_parent->Transform.ViewMatrix() );
}

const glm::mat4 CCameraComponent::ViewProjectionMatrix() const
{
	return( ProjectionMatrix() * m_parent->Transform.ViewMatrix() );
}
