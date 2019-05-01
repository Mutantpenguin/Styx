#pragma once

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP>		CuboidP( const float width, const float height, const float depth );
	Geometry<VertexPU0>		CuboidPU0( const float width, const float height, const float depth );
	Geometry<VertexPNU0>	CuboidPNU0( const float width, const float height, const float depth );
}