#include "CTimer.hpp"

CTimer::CTimer( void ) :
	m_startTime { std::chrono::high_resolution_clock::now() },
	m_currentTime { m_startTime },
	m_lastTime { m_currentTime }
{
}

void CTimer::Update( void )
{
	// TODO implement smoothing?

	m_lastTime		= m_currentTime;
	m_currentTime	= std::chrono::high_resolution_clock::now();

	m_dT = std::chrono::duration_cast< std::chrono::milliseconds >( m_currentTime - m_lastTime ).count() / 1000.0f;

	m_time = std::chrono::duration_cast< std::chrono::microseconds >( m_currentTime - m_startTime ).count();
}
