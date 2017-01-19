#ifndef CTIMER_HPP
#define CTIMER_HPP

#include <cstdint>
#include <chrono>

class CTimer final
{
friend class CEngine;

public:
	inline float dT( void ) const
	{
		return( m_dT );
	};

	inline std::uint64_t Time( void ) const
	{
		return( m_time );
	};

private:
	CTimer( void );

	void	Update( void );

private:
	const std::chrono::high_resolution_clock::time_point	m_startTime;

	std::chrono::high_resolution_clock::time_point	m_currentTime;
	std::chrono::high_resolution_clock::time_point	m_lastTime;

	float	m_dT { 0.0f };

	std::uint64_t m_time { 0 };
};

#endif // CTIMER_HPP
