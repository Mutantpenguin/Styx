#include "RenderPackage.hpp"

#include <algorithm>

void RenderPackage::SortDrawCommands()
{
	for( auto &layer : m_renderLayers )
	{
		layer.SortDrawCommands();
	}
}