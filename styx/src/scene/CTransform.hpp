#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "src/core/Types.hpp"

class CTransform final
{
public:
	glm::vec3	Position	{ 0.0f, 0.0f, 0.0f };
	glm::quat	Orientation	{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	Scale		{ 1.0f, 1.0f, 1.0f };

	void Direction( const glm::vec3 &direction );
	[[nodiscard]] const glm::vec3 Direction() const;

	[[nodiscard]] glm::vec3 const Up() const;

	void Rotate( const f16 pitchAngle, const f16 yawAngle, const f16 rollAngle );

	[[nodiscard]] const glm::mat4 ViewMatrix() const;

	[[ nodiscard ]] const glm::mat4 ModelMatrix() const;

private:
	
	
};
