#include "src/geometry/prefabs/Rectangle.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> RectangleP( const float width, const float height )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;

		Geometry<VertexP> geometry = {
											{
												{	{ -halfwidth, -halfheight, 0.0f }	},
												{	{ +halfwidth, -halfheight, 0.0f }	},
												{	{ -halfwidth, +halfheight, 0.0f }	},
												{	{ +halfwidth, +halfheight, 0.0f }	}
											}
		};

		return( geometry );
	}

	Geometry<VertexPNU0> RectanglePNU0( const float width, const float height )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;

		Geometry<VertexPNU0> geometry = {
											{
												{	{ -halfwidth, -halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f, +1.0f }	}
											}
		};

		return( geometry );
	}
}