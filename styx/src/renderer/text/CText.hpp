#pragma once

#include <memory>
#include <string>

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

class CText final
{
public:
	CText();
	~CText();

	std::string Value;

	Geometry<VertexPCU0> Geometry;
};

