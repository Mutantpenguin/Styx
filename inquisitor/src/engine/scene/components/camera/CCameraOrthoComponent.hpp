#ifndef CCAMERAORTHOCOMPONENT_HPP
#define CCAMERAORTHOCOMPONENT_HPP

#include "src/engine/helper/CSize.hpp"

#include "src/engine/scene/components/camera/CCameraComponent.hpp"

class CCameraOrthoComponent final : public CCameraComponent
{
private:
	CCameraOrthoComponent( const CCameraOrthoComponent& rhs );
	CCameraOrthoComponent& operator=( const CCameraOrthoComponent& rhs );

public:
	CCameraOrthoComponent( const std::shared_ptr< CEntity > &parent, const CSize &size, float zNear, float zFar );
	~CCameraOrthoComponent() {};

public:
	[[nodiscard]] virtual const glm::mat4 ProjectionMatrix( void ) const override;

private:
	const CSize m_size;
};

#endif // CCAMERAORTHOCOMPONENT_HPP
