#include "src/geometry/prefabs/Quad.hpp"

#include "src/geometry/prefabs/Rectangle.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> QuadP( const float size )
	{
		return( RectangleP( size, size ) );
	}

	Geometry<VertexPNU0> QuadPNU0( const float size )
	{
		return( RectanglePNU0( size, size ) );
	}
}