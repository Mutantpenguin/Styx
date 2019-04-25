#pragma once

#include "src/renderer/GL.h"

#include "src/helper/geom/Primitives.hpp"

class CVBO final
{
public:
	CVBO( const Primitives::SPrimitive &primitive );
	~CVBO();

	size_t VertexCount() const
	{
		return( m_vertexCount );
	}

	GLuint GLID;

private:
	const size_t m_vertexCount;
};