#include "RenderPackage.hpp"

#include <algorithm>

void RenderPackage::SortDrawCommands()
{
	for( auto &layer : RenderLayers )
	{
		layer.SortDrawCommands();
	}
}