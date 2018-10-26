#ifndef MATH_HPP
#define MATH_HPP

#include "src/engine/helper/Types.hpp"

namespace Math
{
	/** Checks if "number" is a power of two; zero and one are powers of two too. */
	bool	IsPowerOfTwo( const i32 number );

	/** Creates a random float between min and max. */
	float	frand( const float min, const float max );

	/** Creates a random 32bit integer between min and max. */
	i32	irand( const i32 min, const i32 max );
}

#endif // MATH_HPP
