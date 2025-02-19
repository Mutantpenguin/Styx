#pragma once

#include <array>

#include "src/core/Types.hpp"

#include "src/helper/geom/CPlane.hpp"

class CFrustum
{
public:
	CFrustum() = delete;

	explicit CFrustum( const glm::mat4 &viewProjectionMatrix );

	bool IsSphereInside( const glm::vec3 &position, const f16 sphereRadius ) const;

private:
	const std::array<CPlane, 6> m_planes;
};