#ifndef CTIMER_HPP
#define CTIMER_HPP

#include <cstdint>
#include <chrono>

class CTimer final
{
public:
	CTimer( void );

	[[nodiscard]] inline std::uint64_t Time( void ) const
	{
		return( std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::high_resolution_clock::now() - m_startTime ).count() );
	};

private:
	CTimer( const CTimer &rhs ) = delete;
	CTimer& operator = ( const CTimer &rhs ) = delete;

private:
	const std::chrono::high_resolution_clock::time_point	m_startTime;
};

#endif // CTIMER_HPP
