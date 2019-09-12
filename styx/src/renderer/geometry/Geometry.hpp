#pragma once

#include <vector>
#include <algorithm>

#include "src/renderer/GL.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "src/core/Types.hpp"

template<typename T>
struct Geometry final
{
	GLenum Mode;
	
	std::vector<T> Vertices;

	std::vector<u32> Indices;

	const size_t Stride = sizeof( T );

	[[ nodiscard ]] glm::vec3 CalculateBoundingSphereRadiusVector() const
	{
		if( Vertices.size() > 0 )
		{
			return( ( *std::max_element( std::cbegin( Vertices ), std::cend( Vertices ), []( const T &a, const T &b ) { return( glm::length2( a.Position ) < glm::length2( b.Position ) ); } ) ).Position );
		}
		else
		{
			return( glm::vec3() );
		}
	}
};