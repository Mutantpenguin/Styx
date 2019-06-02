#pragma once

#include "src/renderer/GL.h"

enum class AttributeLocation : GLint
{
	position = 0,
	normal,
	tangent,
	bitangent,
	color,
	uv0,
	uv1,
	uv2,
	uv3
};