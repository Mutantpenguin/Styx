#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "src/core/Types.hpp"

class CTransform final
{
public:
	void Position( const glm::vec3 &position );
	[[nodiscard]] const glm::vec3 &Position() const;
	
	void Orientation( const glm::quat &orientation );
	[[nodiscard]] const glm::quat &Orientation() const;

	void Scale( const glm::vec3 &position );
	[[nodiscard]] const glm::vec3 &Scale() const;

	void Direction( const glm::vec3 &direction );
	[[nodiscard]] const glm::vec3 Direction() const;

	[[nodiscard]] glm::vec3 const Up() const;

	void Rotate( const f16 pitchAngle, const f16 yawAngle, const f16 rollAngle );

	[[nodiscard]] const glm::mat4 ViewMatrix() const;

	[[ nodiscard ]] const glm::mat4 ModelMatrix() const;

private:
	glm::vec3	m_position		{ 0.0f, 0.0f, 0.0f };
	glm::quat	m_orientation	{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	m_scale			{ 1.0f, 1.0f, 1.0f };
};
