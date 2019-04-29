#include "src/geometry/prefabs/Cuboid.hpp"


namespace GeometryPrefabs
{
	Geometry<VertexPNU0> CuboidPNU0( const float width, const float height, const float depth )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;
		const auto halfdepth = depth / 2.0f;

		Geometry<VertexPNU0> geometry = {
											{
				// back
				{	{ +halfwidth, -halfheight, -halfdepth }, {  0.0f,  0.0f, -1.0f }, {  0.0f, +1.0f }	},
				{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f,  0.0f, -1.0f }, {  0.0f,  0.0f }	},
				{	{ -halfwidth, +halfheight, -halfdepth }, {  0.0f,  0.0f, -1.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, +halfheight, -halfdepth }, {  0.0f,  0.0f, -1.0f }, { +1.0f,  0.0f }	},
				{	{ +halfwidth, +halfheight, -halfdepth }, {  0.0f,  0.0f, -1.0f }, { +1.0f, +1.0f }	},
				{	{ +halfwidth, -halfheight, -halfdepth }, {  0.0f,  0.0f, -1.0f }, {  0.0f, +1.0f }	},

				// left
				{	{ -halfwidth, +halfheight, -halfdepth }, { -1.0f,  0.0f,  0.0f }, {  0.0f, +1.0f }	},
				{	{ -halfwidth, -halfheight, -halfdepth }, { -1.0f,  0.0f,  0.0f }, {  0.0f,  0.0f }	},
				{	{ -halfwidth, -halfheight, +halfdepth }, { -1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, -halfheight, +halfdepth }, { -1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, +halfheight, +halfdepth }, { -1.0f,  0.0f,  0.0f }, { +1.0f,  1.0f }	},
				{	{ -halfwidth, +halfheight, -halfdepth }, { -1.0f,  0.0f,  0.0f }, {  0.0f,  1.0f }	},

				// right
				{	{ +halfwidth, +halfheight, +halfdepth }, { +1.0f,  0.0f,  0.0f }, {  0.0f, +1.0f }	},
				{	{ +halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f,  0.0f }, {  0.0f,  0.0f }	},
				{	{ +halfwidth, -halfheight, -halfdepth }, { +1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ +halfwidth, -halfheight, -halfdepth }, { +1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ +halfwidth, +halfheight, -halfdepth }, { +1.0f,  0.0f,  0.0f }, { +1.0f, +1.0f }	},
				{	{ +halfwidth, +halfheight, +halfdepth }, { +1.0f,  0.0f,  0.0f }, {  0.0f, +1.0f }	},

				// front
				{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f,  0.0f, +1.0f }, {  0.0f, +1.0f }	},
				{	{ -halfwidth, +halfheight, +halfdepth }, {  0.0f,  0.0f, +1.0f }, {  0.0f,  0.0f }	},
				{	{ -halfwidth, -halfheight, +halfdepth }, {  0.0f,  0.0f, +1.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, -halfheight, +halfdepth }, {  0.0f,  0.0f, +1.0f }, { +1.0f,  0.0f }	},
				{	{ +halfwidth, -halfheight, +halfdepth }, {  0.0f,  0.0f, +1.0f }, { +1.0f, +1.0f }	},
				{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f,  0.0f, +1.0f }, {  0.0f, +1.0f }	},

				// top
				{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f,  0.0f }, {  0.0f, +1.0f }	},
				{	{ +halfwidth, +halfheight, -halfdepth }, {  0.0f, +1.0f,  0.0f }, {  0.0f,  0.0f }	},
				{	{ -halfwidth, +halfheight, -halfdepth }, {  0.0f, +1.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, +halfheight, -halfdepth }, {  0.0f, +1.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f,  0.0f }, { +1.0f, +1.0f }	},
				{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f,  0.0f }, {  0.0f, +1.0f }	},

				// bottom
				{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f, -1.0f,  0.0f }, {  0.0f, +1.0f }	},
				{	{ +halfwidth, -halfheight, -halfdepth }, {  0.0f, -1.0f,  0.0f }, {  0.0f,  0.0f }	},
				{	{ +halfwidth, -halfheight, +halfdepth }, {  0.0f, -1.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ +halfwidth, -halfheight, +halfdepth }, {  0.0f, -1.0f,  0.0f }, { +1.0f,  0.0f }	},
				{	{ -halfwidth, -halfheight, +halfdepth }, {  0.0f, -1.0f,  0.0f }, { +1.0f, +1.0f }	},
				{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f, -1.0f,  0.0f }, {  0.0f, +1.0f }	}
			}
		};

		return( geometry );
	}
}