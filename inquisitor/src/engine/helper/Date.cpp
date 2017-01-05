#include "Date.hpp"

#include <chrono>

#include "src/ext/fmt/time.h"

namespace Date
{
	std::string GetCurrentDateTimeString( void )
	{
		const std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		const std::time_t time = std::chrono::system_clock::to_time_t( p );

		return( fmt::format( "{0:%Y-%m-%d_%H:%M:%S}", fmt::localtime( time ) ) );
	}
}
