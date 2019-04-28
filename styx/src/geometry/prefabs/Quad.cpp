#include "src/geometry/prefabs/Quad.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> QuadP( const float size )
	{
		const auto halfsize = size / 2.0f;

		Geometry<VertexP> geometry = {
											{
												{	{ -halfsize, -halfsize, 0.0f }	},
												{	{ +halfsize, -halfsize, 0.0f }	},
												{	{ -halfsize, +halfsize, 0.0f }	},
												{	{ +halfsize, +halfsize, 0.0f }	}
											}
		};

		return( geometry );
	}

	Geometry<VertexPNU0> QuadPNU0( const float size )
	{
		const auto halfsize = size / 2.0;

		Geometry<VertexPNU0> geometry = {
											{
												{	{ -halfsize, -halfsize, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f,  0.0f }	},
												{	{ +halfsize, -halfsize, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f, +1.0f }	},
												{	{ +halfsize, +halfsize, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f, +1.0f }	}
											}
										};

		return( geometry );
	}
}