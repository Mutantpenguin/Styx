#include "Math.hpp"

#include <cstdlib>

namespace Math
{
	bool IsPowerOfTwo( const i32 number )
	{
		return( ( number & ( number - 1 ) ) == 0 );
	}

	float frand( const float min, const float max )
	{
		return( min + ( static_cast< float >( std::rand() ) / static_cast< float >( RAND_MAX ) ) * ( max - min ) );
	}

	i32 irand( const i32 min, const i32 max )
	{
		return( min + (std::rand()%(max-min+1) ) );
	}
}
