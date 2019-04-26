#include "src/geometry/prefabs/Quad.hpp"

namespace GeometryPrefabs
{
	// TODO use the size
	Geometry<VertexPNU0> QuadPNU0( const float size )
	{
		Geometry<VertexPNU0> geometry = {
											{
												{	{ -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f,  0.0f }	},
												{	{ +1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f,  0.0f }	},
												{	{ -1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f, +1.0f }	},
												{	{ +1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f, +1.0f }	}
											}
										};

		return( geometry );
	}
}