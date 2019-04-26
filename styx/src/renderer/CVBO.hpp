#pragma once

#include "src/renderer/GL.h"

class CVBO final
{
public:
	CVBO( const size_t size, const void * data );
	~CVBO();

	GLuint GLID;
};