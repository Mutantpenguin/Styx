#include "Math.hpp"

#include <cstdlib>

namespace Math
{
	bool IsPowerOfTwo( int number )
	{
		return( ( number & ( number - 1 ) ) == 0 );
	}

	float frand( float min, float max )
	{
		return( min + ( static_cast< float >( rand() ) / static_cast< float >( RAND_MAX ) ) * ( max - min ) );
	}

	int irand( int min, int max )
	{
		return( min + (rand()%(max-min+1) ) );
	}
}
