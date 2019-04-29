#pragma once

#include "src/geometry/Geometry.hpp"
#include "src/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> RectangleP( const float width, const float height );
	Geometry<VertexPNU0> RectanglePNU0( const float width, const float height );
}