#include "RenderPackage.hpp"

#include <algorithm>

void RenderPackage::SortDrawCommands()
{
	// TODO multithreaded?
	// TODO comment whats going on here

	std::sort( std::begin( drawCommands ), std::end( drawCommands ),
		[]( const RenderPackage::DrawCommand &a, const RenderPackage::DrawCommand &b ) -> bool
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