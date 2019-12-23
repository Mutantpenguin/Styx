#pragma once

#include <vector>

#include "src/helper/CColor.hpp"

#include "RenderLayer.hpp"

struct RenderPackage final
{
	CColor ClearColor;
	
	glm::uint TimeMilliseconds;
	
	std::vector<RenderLayer> RenderLayers;

	void SortDrawCommands();
};