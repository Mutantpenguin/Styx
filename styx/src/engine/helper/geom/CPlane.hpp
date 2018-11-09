#pragma once

#include <glm/glm.hpp>

#include "src/engine/helper/Types.hpp"

class CPlane
{
public:
	CPlane();

	CPlane( const glm::vec3 &point, const glm::vec3 &normal );

	void SetNormal( const glm::vec3 &normal );
	const glm::vec3 &Normal() const;

	void SetDistance( f16 distance );
	f16 Distance() const;

	void Normalize();

	f16 DistanceToPlane( const glm::vec3 &point ) const;

private:
	glm::vec3	m_normal	{ 0.0f, 0.0f, 0.0f };
	f16			m_distance	{ 0.0f };
};
