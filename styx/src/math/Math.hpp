#pragma once

#include "src/core/Types.hpp"

namespace Math
{
	/** Checks if "number" is a power of two; zero and one are powers of two too. */
	bool	IsPowerOfTwo( const s32 number );

	/** Creates a random float between min and max. */
	f16	frand( const f16 min, const f16 max );

	/** Creates a random 32bit integer between min and max. */
	s32	irand( const s32 min, const s32 max );
}
