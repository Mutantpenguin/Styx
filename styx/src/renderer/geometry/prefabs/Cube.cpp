#include "Cube.hpp"

#include "Cuboid.hpp"


namespace GeometryPrefabs
{
	Geometry<VertexP> CubeP( const float size )
	{
		return( CuboidP( size, size, size ) );
	}
	
	Geometry<VertexPU0> CubePU0( const float size )
	{
		return( CuboidPU0( size, size, size ) );
	}
	
	Geometry<VertexPNU0> CubePNU0( const float size )
	{
		return( CuboidPNU0( size, size, size ) );
	}
}