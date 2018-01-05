#ifndef CTIMER_HPP
#define CTIMER_HPP

#include <cstdint>
#include <chrono>

class CTimer final
{
public:
	CTimer( void );

	[[nodiscard]] std::uint64_t Time( void ) const;

	void Pause( void );
	void Resume( void );

private:
	CTimer( const CTimer &rhs ) = delete;
	CTimer& operator = ( const CTimer &rhs ) = delete;

	enum class eStatus
	{
		RUNNING,
		PAUSED
	};

	const std::chrono::high_resolution_clock::time_point	m_startTime;

	eStatus m_status = eStatus::RUNNING;

	std::chrono::high_resolution_clock::time_point	m_pauseStartTime;

	std::uint64_t	m_accumulatedPausedTime { 0 };
};

#endif // CTIMER_HPP
