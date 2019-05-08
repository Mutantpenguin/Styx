#include "Math.hpp"

#include <cstdlib>

namespace Math
{
	bool IsPowerOfTwo( const i32 number )
	{
		return( ( number & ( number - 1 ) ) == 0 );
	}

	f16 frand( const f16 min, const f16 max )
	{
		return( min + ( static_cast<f16>( std::rand() ) / static_cast<f16>( RAND_MAX ) ) * ( max - min ) );
	}

	i32 irand( const i32 min, const i32 max )
	{
		return( min + (std::rand()%(max-min+1) ) );
	}
}
