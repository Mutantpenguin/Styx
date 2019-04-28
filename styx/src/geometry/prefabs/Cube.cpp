#include "src/geometry/prefabs/Cube.hpp"


namespace GeometryPrefabs
{
	Geometry<VertexPNU0> CubePNU0( const float size )
	{
		const auto halfsize = size / 2.0f;

		Geometry<VertexPNU0> geometry = {
											{
												// back
												{	{ +halfsize, -halfsize, -halfsize }, {  0.0f,  0.0f, -1.0f }, {  0.0f, +1.0f }	},
												{	{ -halfsize, -halfsize, -halfsize }, {  0.0f,  0.0f, -1.0f }, {  0.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, -halfsize }, {  0.0f,  0.0f, -1.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, -halfsize }, {  0.0f,  0.0f, -1.0f }, { +1.0f,  0.0f }	},
												{	{ +halfsize, +halfsize, -halfsize }, {  0.0f,  0.0f, -1.0f }, { +1.0f, +1.0f }	},
												{	{ +halfsize, -halfsize, -halfsize }, {  0.0f,  0.0f, -1.0f }, {  0.0f, +1.0f }	},

												// left
												{	{ -halfsize, +halfsize, -halfsize }, { -1.0f,  0.0f,  0.0f }, {  0.0f, +1.0f }	},
												{	{ -halfsize, -halfsize, -halfsize }, { -1.0f,  0.0f,  0.0f }, {  0.0f,  0.0f }	},
												{	{ -halfsize, -halfsize, +halfsize }, { -1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, -halfsize, +halfsize }, { -1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, +halfsize }, { -1.0f,  0.0f,  0.0f }, { +1.0f,  1.0f }	},
												{	{ -halfsize, +halfsize, -halfsize }, { -1.0f,  0.0f,  0.0f }, {  0.0f,  1.0f }	},

												// right
												{	{ +halfsize, +halfsize, +halfsize }, { +1.0f,  0.0f,  0.0f }, {  0.0f, +1.0f }	},
												{	{ +halfsize, -halfsize, +halfsize }, { +1.0f,  0.0f,  0.0f }, {  0.0f,  0.0f }	},
												{	{ +halfsize, -halfsize, -halfsize }, { +1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ +halfsize, -halfsize, -halfsize }, { +1.0f,  0.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ +halfsize, +halfsize, -halfsize }, { +1.0f,  0.0f,  0.0f }, { +1.0f, +1.0f }	},
												{	{ +halfsize, +halfsize, +halfsize }, { +1.0f,  0.0f,  0.0f }, {  0.0f, +1.0f }	},

												// front
												{	{ +halfsize, +halfsize, +halfsize }, {  0.0f,  0.0f, +1.0f }, {  0.0f, +1.0f }	},
												{	{ -halfsize, +halfsize, +halfsize }, {  0.0f,  0.0f, +1.0f }, {  0.0f,  0.0f }	},
												{	{ -halfsize, -halfsize, +halfsize }, {  0.0f,  0.0f, +1.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, -halfsize, +halfsize }, {  0.0f,  0.0f, +1.0f }, { +1.0f,  0.0f }	},
												{	{ +halfsize, -halfsize, +halfsize }, {  0.0f,  0.0f, +1.0f }, { +1.0f, +1.0f }	},
												{	{ +halfsize, +halfsize, +halfsize }, {  0.0f,  0.0f, +1.0f }, {  0.0f, +1.0f }	},

												// top
												{	{ +halfsize, +halfsize, +halfsize }, {  0.0f, +1.0f,  0.0f }, {  0.0f, +1.0f }	},
												{	{ +halfsize, +halfsize, -halfsize }, {  0.0f, +1.0f,  0.0f }, {  0.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, -halfsize }, {  0.0f, +1.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, -halfsize }, {  0.0f, +1.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, +halfsize, +halfsize }, {  0.0f, +1.0f,  0.0f }, { +1.0f, +1.0f }	},
												{	{ +halfsize, +halfsize, +halfsize }, {  0.0f, +1.0f,  0.0f }, {  0.0f, +1.0f }	},

												// bottom
												{	{ -halfsize, -halfsize, -halfsize }, {  0.0f, -1.0f,  0.0f }, {  0.0f, +1.0f }	},
												{	{ +halfsize, -halfsize, -halfsize }, {  0.0f, -1.0f,  0.0f }, {  0.0f,  0.0f }	},
												{	{ +halfsize, -halfsize, +halfsize }, {  0.0f, -1.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ +halfsize, -halfsize, +halfsize }, {  0.0f, -1.0f,  0.0f }, { +1.0f,  0.0f }	},
												{	{ -halfsize, -halfsize, +halfsize }, {  0.0f, -1.0f,  0.0f }, { +1.0f, +1.0f }	},
												{	{ -halfsize, -halfsize, -halfsize }, {  0.0f, -1.0f,  0.0f }, {  0.0f, +1.0f }	}
											}
										};

		return( geometry );
	}
}