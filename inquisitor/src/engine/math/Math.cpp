#include "Math.hpp"

#include <cstdlib>

namespace Math
{
	bool IsPowerOfTwo( std::int32_t number )
	{
		return( ( number & ( number - 1 ) ) == 0 );
	}

	float frand( float min, float max )
	{
		return( min + ( static_cast< float >( rand() ) / static_cast< float >( RAND_MAX ) ) * ( max - min ) );
	}

	std::int32_t irand( std::int32_t min, std::int32_t max )
	{
		return( min + (rand()%(max-min+1) ) );
	}
}
