#pragma once

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP>		RectangleP( const float width, const float height );
	Geometry<VertexPU0>		RectanglePU0( const float width, const float height );
	Geometry<VertexPNU0>	RectanglePNU0( const float width, const float height );
}