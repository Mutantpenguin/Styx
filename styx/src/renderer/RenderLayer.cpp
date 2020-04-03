#include "RenderLayer.hpp"

#include <algorithm>

void RenderLayer::SortDrawCommands()
{
	// TODO multithreaded?
	// TODO comment whats going on here

	std::sort( std::begin( drawCommands ), std::end( drawCommands ),
		[]( const RenderLayer::DrawCommand &a, const RenderLayer::DrawCommand &b ) -> bool
		{
			if( !a.blending && b.blending )
			{
				return( true );
			}
			else if( a.blending && !b.blending )
			{
				return( false );
			}
			else if( a.blending )
			{
				return( a.viewDepth > b.viewDepth );
			}
			else
			{
				if( a.material > b.material )
				{
					return( true );
				}
				else if( a.material < b.material )
				{
					return( false );
				}
				else
				{
					return( a.viewDepth < b.viewDepth );
				}
			}
		} );
}
