#pragma once

#include <string>

#include "src/renderer/GL.h"

struct SShaderInterface final
{
	std::string name;
	GLenum		type;
};
