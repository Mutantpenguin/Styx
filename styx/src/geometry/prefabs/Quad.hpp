#pragma once

#include "src/geometry/Geometry.hpp"
#include "src/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> QuadP( const float size = 1.0f );
	Geometry<VertexPNU0> QuadPNU0( const float size = 1.0f );
}