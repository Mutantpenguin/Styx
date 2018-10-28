#pragma once

#include <array>

#include "src/engine/helper/geom/CPlane.hpp"

class CFrustum
{
public:
	explicit CFrustum( const glm::mat4 &viewProjectionMatrix );

	bool IsSphereInside( const glm::vec3 &position, const float sphereRadius ) const;

private:
	std::array< CPlane, 6 > m_planes;
};
