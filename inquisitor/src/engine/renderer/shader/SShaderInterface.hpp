#ifndef SSHADERINTERFACE_HPP
#define SSHADERINTERFACE_HPP

#include <string>

#include "src/engine/renderer/GL.h"

struct SShaderInterface
{
	std::string name;
	GLenum		type;
};

#endif
