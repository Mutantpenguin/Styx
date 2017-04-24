#ifndef MATH_HPP
#define MATH_HPP

#include <cstdint>

namespace Math
{
	/** Checks if "number" is a power of two; zero and one are powers of two too. */
	bool	IsPowerOfTwo( const std::int32_t number );

	/** Creates a random float between min and max. */
	float	frand( const float min, const float max );

	/** Creates a random 32bit integer between min and max. */
	std::int32_t	irand( const std::int32_t min, const std::int32_t max );
}

#endif // MATH_HPP
