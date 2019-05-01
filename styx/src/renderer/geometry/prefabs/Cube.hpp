#pragma once

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP>		CubeP( const float size = 1.0f );
	Geometry<VertexPU0>		CubePU0( const float size = 1.0f );
	Geometry<VertexPNU0>	CubePNU0( const float size = 1.0f );
}