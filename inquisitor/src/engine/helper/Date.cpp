#include "Date.hpp"

#include <chrono>
#include <iomanip>

namespace Date
{
	std::string GetCurrentDateTimeString( void )
	{
		const std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		const std::time_t tm = std::chrono::system_clock::to_time_t( p );

		std::ostringstream oss;
		oss << std::put_time( std::localtime( &tm ), "%Y-%m-%d_%H:%M:%S" );

		return( oss.str() );
	}
}
