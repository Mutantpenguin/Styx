#include "CTimer.hpp"

CTimer::CTimer() :
	m_startTime { std::chrono::high_resolution_clock::now() },
	m_pauseStartTime { m_startTime }
{
}

u64 CTimer::Time() const
{
	return( std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - m_startTime ).count() - m_accumulatedPausedTime );
}

void CTimer::Pause()
{
	if( eStatus::RUNNING == m_status )
	{
		m_pauseStartTime = std::chrono::high_resolution_clock::now();

		m_status = eStatus::PAUSED;
	}
}

void CTimer::Resume()
{
	if( eStatus::PAUSED == m_status )
	{
		m_accumulatedPausedTime += std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - m_pauseStartTime ).count();

		m_status = eStatus::RUNNING;
	}
}
