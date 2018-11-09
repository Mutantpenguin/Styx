#include "CPlane.hpp"

CPlane::CPlane()
{
}

CPlane::CPlane( const glm::vec3 &point, const glm::vec3 &normal ) :
	m_normal { normal },
	m_distance { -glm::dot( normal, point ) }
{
	Normalize();
}

void CPlane::SetNormal( const glm::vec3 &normal )
{
	m_normal = normal;
}

const glm::vec3 &CPlane::Normal() const
{
	return( m_normal );
}

void CPlane::SetDistance( f16 distance )
{
	m_distance = distance;
}

f16 CPlane::Distance() const
{
	return( m_distance );
}

void CPlane::Normalize()
{
	const f16 length = 1.0f / glm::length( m_normal );
	m_normal	*= length;
	m_distance	*= length;
}

f16 CPlane::DistanceToPlane( const glm::vec3 &point ) const
{
	return( glm::dot( m_normal, point ) + m_distance );
}
