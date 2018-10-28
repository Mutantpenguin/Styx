#pragma once

#include <glm/glm.hpp>

class CPlane
{
public:
	CPlane();

	CPlane( const glm::vec3 &point, const glm::vec3 &normal );

	void SetNormal( const glm::vec3 &normal );
	const glm::vec3 &Normal() const;

	void SetDistance( float distance );
	float Distance() const;

	void Normalize();

	float DistanceToPlane( const glm::vec3 &point ) const;

private:
	glm::vec3	m_normal	{ 0.0f, 0.0f, 0.0f };
	float		m_distance	{ 0.0f };
};
