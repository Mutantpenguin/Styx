#pragma once

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP>		QuadP( const float size = 1.0f );
	Geometry<VertexPU0>		QuadPU0( const float size = 1.0f );
	Geometry<VertexPNU0>	QuadPNU0( const float size = 1.0f );
}