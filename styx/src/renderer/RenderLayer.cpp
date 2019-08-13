#include "RenderLayer.hpp"

#include <algorithm>

void RenderLayer::SortDrawCommands()
{
	// TODO multithreaded?
	// TODO comment whats going on here

	std::sort( std::begin( drawCommands ), std::end( drawCommands ),
		[]( const RenderLayer::DrawCommand &a, const RenderLayer::DrawCommand &b ) -> bool
		{
			if( !a.material->Blending() && b.material->Blending() )
			{
				return( true );
			}
			else if( a.material->Blending() && !b.material->Blending() )
			{
				return( false );
			}
			else if( a.material->Blending() )
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
