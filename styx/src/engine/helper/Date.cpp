#include "Date.hpp"

#include <chrono>

namespace Date
{
	std::time_t GetCurrentDateTime( void )
	{
		const std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		return( std::chrono::system_clock::to_time_t( p ) );
	}
}
