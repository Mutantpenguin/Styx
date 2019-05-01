#include "Cuboid.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> CuboidP( const float width, const float height, const float depth )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;
		const auto halfdepth = depth / 2.0f;

		Geometry<VertexP> geometry =	{
											GL_TRIANGLES,
											{
												// front
												{	{ -halfwidth, -halfheight, +halfdepth }	},
												{	{ +halfwidth, -halfheight, +halfdepth }	},
												{	{ +halfwidth, +halfheight, +halfdepth }	},
												{	{ -halfwidth, +halfheight, +halfdepth }	},
												// back
												{	{ -halfwidth, -halfheight, -halfdepth }	},
												{	{ +halfwidth, -halfheight, -halfdepth }	},
												{	{ +halfwidth, +halfheight, -halfdepth }	},
												{	{ -halfwidth, +halfheight, -halfdepth }	}
											},
											{
												{
													// front
													0, 1, 2,
													2, 3, 0,
													// right
													1, 5, 6,
													6, 2, 1,
													// back
													7, 6, 5,
													5, 4, 7,
													// left
													4, 0, 3,
													3, 7, 4,
													// bottom
													4, 5, 1,
													1, 0, 4,
													// top
													3, 2, 6,
													6, 7, 3
												}
											}
										};

		return( geometry );
	}
	
	Geometry<VertexPU0> CuboidPU0( const float width, const float height, const float depth )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;
		const auto halfdepth = depth / 2.0f;

		Geometry<VertexPU0> geometry = {
											GL_TRIANGLES,
											{
												// back
												{	{ +halfwidth, -halfheight, -halfdepth }, {  0.0f, +1.0f }	},
												{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, -halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, -halfdepth }, { +1.0f,  0.0f }	},
												{	{ +halfwidth, +halfheight, -halfdepth }, { +1.0f, +1.0f }	},
												{	{ +halfwidth, -halfheight, -halfdepth }, {  0.0f, +1.0f }	},

												// left
												{	{ -halfwidth, +halfheight, -halfdepth }, {  0.0f, +1.0f }	},
												{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f,  0.0f }	},
												{	{ -halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, +halfdepth }, { +1.0f,  1.0f }	},
												{	{ -halfwidth, +halfheight, -halfdepth }, {  0.0f,  1.0f }	},

												// right
												{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f }	},
												{	{ +halfwidth, -halfheight, +halfdepth }, {  0.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, -halfdepth }, { +1.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, -halfdepth }, { +1.0f,  0.0f }	},
												{	{ +halfwidth, +halfheight, -halfdepth }, { +1.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f }	},

												// front
												{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f }	},
												{	{ -halfwidth, +halfheight, +halfdepth }, {  0.0f,  0.0f }	},
												{	{ -halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, +halfdepth }, { +1.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f }	},

												// top
												{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, -halfdepth }, {  0.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, -halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, -halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, +halfdepth }, { +1.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, +halfdepth }, {  0.0f, +1.0f }	},

												// bottom
												{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f, +1.0f }	},
												{	{ +halfwidth, -halfheight, -halfdepth }, {  0.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, +halfdepth }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, -halfheight, +halfdepth }, { +1.0f, +1.0f }	},
												{	{ -halfwidth, -halfheight, -halfdepth }, {  0.0f, +1.0f }	}
											},
											{
												{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 }
											}
										};

		return( geometry );
	}
	
	Geometry<VertexPNU0> CuboidPNU0( const float width, const float height, const float depth )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;
		const auto halfdepth = depth / 2.0f;

		Geometry<VertexPNU0> geometry = {
											GL_TRIANGLES,
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
											},
											{
												{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 }
											}
										};

		return( geometry );
	}
}