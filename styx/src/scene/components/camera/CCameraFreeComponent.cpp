#include "CCameraFreeComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "src/scene/CWorld.hpp"

CCameraFreeComponent::CCameraFreeComponent( const std::shared_ptr< CEntity > &parent, const f16 aspectRatio, const f16 fov, const f16 zNear, const f16 zFar ) :
	CCameraComponent( parent, zNear, zFar ),
	m_aspectRatio { aspectRatio },
	m_fov { fov }
{
}

void CCameraFreeComponent::FOV( const f16 fov )
{
	if( fov > 155 )
	{
		m_fov = 155;
	}
	else if( fov < 25 )
	{
		m_fov = 25;
	}
	else
	{
		m_fov = fov;
	}
}

f16 CCameraFreeComponent::FOV() const
{
	return( m_fov );
}

void CCameraFreeComponent::MoveForward( const f16 distance )
{
	auto &transform = m_parent->Transform;
	transform.Position( transform.Position() - ( transform.Direction() * distance ) );
}

void CCameraFreeComponent::MoveBackward( const f16 distance )
{
	auto &transform = m_parent->Transform;
	transform.Position( transform.Position() + ( transform.Direction() * distance ) );
}

void CCameraFreeComponent::MoveUp( const f16 distance )
{
	auto &transform = m_parent->Transform;
	transform.Position( transform.Position() + ( CWorld::Y * distance ) );
}

void CCameraFreeComponent::MoveDown( const f16 distance )
{
	auto &transform = m_parent->Transform;
	transform.Position( transform.Position() - ( CWorld::Y * distance ) );
}

void CCameraFreeComponent::MoveLeft( const f16 distance )
{
	auto &transform = m_parent->Transform;
	transform.Position( transform.Position() - ( glm::cross( transform.Up(), transform.Direction() ) * distance ) );
}

void CCameraFreeComponent::MoveRight( const f16 distance )
{
	auto &transform = m_parent->Transform;
	transform.Position( transform.Position() + ( glm::cross( transform.Up(), transform.Direction() ) * distance ) );
}

void CCameraFreeComponent::Rotate( const f16 pitchAngle, const f16 yawAngle )
{
	auto &transform = m_parent->Transform;
	transform.Orientation( glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * transform.Orientation() * glm::angleAxis( glm::radians( yawAngle ), CWorld::Y ) );
}

const glm::mat4 CCameraFreeComponent::ProjectionMatrix() const
{
	return( glm::perspective( glm::radians( m_fov ), m_aspectRatio, m_zNear, m_zFar ) );
}
