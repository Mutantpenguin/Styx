#pragma once

#include <cstdint>
#include <chrono>

#include "src/engine/helper/Types.hpp"

class CTimer final
{
public:
	CTimer( void );

	[[nodiscard]] u64 Time( void ) const;

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

	u64 m_accumulatedPausedTime { 0 };
};
