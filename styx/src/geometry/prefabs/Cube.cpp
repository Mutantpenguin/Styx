#include "src/geometry/prefabs/Cube.hpp"

#include "src/geometry/prefabs/Cuboid.hpp"


namespace GeometryPrefabs
{
	Geometry<VertexPNU0> CubePNU0( const float size )
	{
		return( CuboidPNU0( size, size, size ) );
	}
}