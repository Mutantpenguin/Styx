#include "CFrustum.hpp"

#include <algorithm>

CFrustum::CFrustum( const glm::mat4 &viewProjectionMatrix ) :
	m_planes {	{
					// right
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] - viewProjectionMatrix[ 0 ][ 0 ],
							viewProjectionMatrix[ 1 ][ 3 ] - viewProjectionMatrix[ 1 ][ 0 ],
							viewProjectionMatrix[ 2 ][ 3 ] - viewProjectionMatrix[ 2 ][ 0 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] - viewProjectionMatrix[ 3 ][ 0 ]
					},

					// left
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] + viewProjectionMatrix[ 0 ][ 0 ],
							viewProjectionMatrix[ 1 ][ 3 ] + viewProjectionMatrix[ 1 ][ 0 ],
							viewProjectionMatrix[ 2 ][ 3 ] + viewProjectionMatrix[ 2 ][ 0 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] + viewProjectionMatrix[ 3 ][ 0 ]
					},

					// top
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] - viewProjectionMatrix[ 0 ][ 1 ],
							viewProjectionMatrix[ 1 ][ 3 ] - viewProjectionMatrix[ 1 ][ 1 ],
							viewProjectionMatrix[ 2 ][ 3 ] - viewProjectionMatrix[ 2 ][ 1 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] - viewProjectionMatrix[ 3 ][ 1 ]
					},

					// bottom
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] + viewProjectionMatrix[ 0 ][ 1 ],
							viewProjectionMatrix[ 1 ][ 3 ] + viewProjectionMatrix[ 1 ][ 1 ],
							viewProjectionMatrix[ 2 ][ 3 ] + viewProjectionMatrix[ 2 ][ 1 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] + viewProjectionMatrix[ 3 ][ 1 ]
					},

					// front
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] + viewProjectionMatrix[ 0 ][ 2 ],
							viewProjectionMatrix[ 1 ][ 3 ] + viewProjectionMatrix[ 1 ][ 2 ],
							viewProjectionMatrix[ 2 ][ 3 ] + viewProjectionMatrix[ 2 ][ 2 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] + viewProjectionMatrix[ 3 ][ 2 ]
					},

					// back
					{
						{
							viewProjectionMatrix[ 0 ][ 3 ] - viewProjectionMatrix[ 0 ][ 2 ],
							viewProjectionMatrix[ 1 ][ 3 ] - viewProjectionMatrix[ 1 ][ 2 ],
							viewProjectionMatrix[ 2 ][ 3 ] - viewProjectionMatrix[ 2 ][ 2 ]
						},
						viewProjectionMatrix[ 3 ][ 3 ] - viewProjectionMatrix[ 3 ][ 2 ]
					}
				} }
{}

bool CFrustum::IsSphereInside( const glm::vec3 &position, const f16 sphereRadius ) const
{
	// TODO multithreaded?
	for( const CPlane &plane : m_planes )
	{
		if( plane.DistanceToPlane( position ) < -sphereRadius )
		{
			return( false );
		}
	}
	
	/* TODO use std::any_of
	if( std::any_of( std::begin( m_planes ), std::end( m_planes ),
	// TODO if( std::any_of( std::execution::parallel_unsequenced_policy, std::begin( m_planes ), std::end( m_planes ),
		[&position, &sphereRadius]( const CPlane &plane )
		{
			return( plane.DistanceToPlane( position ) >= -sphereRadius );
		} ) )
	{
		return( false );
	}
	*/

    return( true );
}
