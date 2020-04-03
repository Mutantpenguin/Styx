#include "RenderLayer.hpp"

#include <algorithm>

void RenderLayer::SortDrawCommands()
{
	// TODO multithreaded?
	// TODO comment whats going on here

	std::sort( std::begin( drawCommands ), std::end( drawCommands ),
		[]( const RenderLayer::DrawCommand &a, const RenderLayer::DrawCommand &b ) -> bool
		{
			const auto aBlending = a.material->Blending();
			const auto bBlending = b.material->Blending();

			if( !aBlending && bBlending )
			{
				return( true );
			}
			else if( aBlending && !bBlending )
			{
				return( false );
			}
			else if( aBlending )
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
