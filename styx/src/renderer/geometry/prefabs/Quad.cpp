#include "Quad.hpp"

#include "Rectangle.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> QuadP( const float size )
	{
		return( RectangleP( size, size ) );
	}

	Geometry<VertexPU0> QuadPU0( const float size )
	{
		return( RectanglePU0( size, size ) );
	}

	Geometry<VertexPNU0> QuadPNU0( const float size )
	{
		return( RectanglePNU0( size, size ) );
	}
}