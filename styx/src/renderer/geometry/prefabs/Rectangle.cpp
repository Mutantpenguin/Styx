#include "Rectangle.hpp"

namespace GeometryPrefabs
{
	Geometry<VertexP> RectangleP( const float width, const float height )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;

		Geometry<VertexP> geometry =	{
											GL_TRIANGLE_STRIP,
											{
												{	{ -halfwidth, -halfheight, 0.0f }	},
												{	{ +halfwidth, -halfheight, 0.0f }	},
												{	{ -halfwidth, +halfheight, 0.0f }	},
												{	{ +halfwidth, +halfheight, 0.0f }	}
											},
											{
												{ 0, 1, 2, 3 }
											}
										};

		return( geometry );
	}
	
	Geometry<VertexPU0> RectanglePU0( const float width, const float height )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;

		Geometry<VertexPU0> geometry = {
											GL_TRIANGLE_STRIP,
											{
												{	{ -halfwidth, -halfheight, 0.0f }, {  0.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, 0.0f }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, 0.0f }, {  0.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, 0.0f }, { +1.0f, +1.0f }	}
											},
											{
												{ 0, 1, 2, 3 }
											}
										};

		return( geometry );
	}

	Geometry<VertexPNU0> RectanglePNU0( const float width, const float height )
	{
		const auto halfwidth = width / 2.0f;
		const auto halfheight = height / 2.0f;

		Geometry<VertexPNU0> geometry = {
											GL_TRIANGLE_STRIP,
											{
												{	{ -halfwidth, -halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f,  0.0f }	},
												{	{ +halfwidth, -halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f,  0.0f }	},
												{	{ -halfwidth, +halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, {  0.0f, +1.0f }	},
												{	{ +halfwidth, +halfheight, 0.0f }, { 0.0f, 0.0f, +1.0f }, { +1.0f, +1.0f }	}
											},
											{
												{ 0, 1, 2, 3 }
											}
										};

		return( geometry );
	}
}