#include "Math.hpp"

#include <cstdlib>

namespace Math
{
	bool IsPowerOfTwo( const std::int32_t number )
	{
		return( ( number & ( number - 1 ) ) == 0 );
	}

	float frand( const float min, const float max )
	{
		return( min + ( static_cast< float >( rand() ) / static_cast< float >( RAND_MAX ) ) * ( max - min ) );
	}

	std::int32_t irand( const std::int32_t min, const std::int32_t max )
	{
		return( min + (rand()%(max-min+1) ) );
	}
}
