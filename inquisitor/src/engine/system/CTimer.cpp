#include "CTimer.hpp"

CTimer::CTimer( void ) :
	m_startTime { std::chrono::high_resolution_clock::now() }
{
}
