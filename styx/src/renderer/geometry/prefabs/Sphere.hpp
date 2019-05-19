#pragma once

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP>		SphereP( const u16 sectorCount, const u16 stackCount, const f16 radius = 1.0f );
	Geometry<VertexPU0>		SpherePU0( const u16 sectorCount, const u16 stackCount, const f16 radius = 1.0f );
}