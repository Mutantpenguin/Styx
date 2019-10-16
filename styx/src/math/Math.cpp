#include "Math.hpp"

#include <cstdlib>

namespace Math
{
	bool IsPowerOfTwo( const s32 number )
	{
		return( ( number & ( number - 1 ) ) == 0 );
	}
}
