#include "CCameraOrthoComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>

CCameraOrthoComponent::CCameraOrthoComponent( const std::shared_ptr<CEntity> &parent, const CSize &size, const f16 zNear, const f16 zFar ) :
	CCameraComponent( parent, zNear, zFar ),
	m_size { size }
{
}

const glm::mat4 CCameraOrthoComponent::ProjectionMatrix() const
{
	return( glm::ortho( 0.0f, static_cast<f16>( m_size.width ), 0.0f, static_cast<f16>( m_size.height ), ZNear, ZFar ) );
}
