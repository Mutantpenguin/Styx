#pragma once

#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

template<typename T>
struct Geometry final
{
	std::vector<T> Vertices;

	// TODO std::vector< u32 > Indices;

	const size_t Stride = sizeof( T );

	[[ nodiscard ]] glm::vec3 BoundingSphereRadiusVector() const
	{
		return( ( *std::max_element( std::cbegin( Vertices ), std::cend( Vertices ), []( const T &a, const T &b ) { return( glm::length2( a.Position ) > glm::length2( b.Position ) ); } ) ).Position );
	}
};