#ifndef MATH_HPP
#define MATH_HPP

namespace Math
{
	/** Checks if "number" is a power of two; zero and one are powers of two too. */
	bool	IsPowerOfTwo( int number );

	/** Creates a random float between min and max. */
	float	frand( float min, float max );

	/** Creates arandom integer between min and max. */
	int		irand( int min, int max );
}

#endif // MATH_HPP
