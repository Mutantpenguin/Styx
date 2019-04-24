#pragma once

#include <cstdint>
#include <chrono>

#include "src/core/Types.hpp"

class CTimer final
{
public:
	CTimer();

	[[nodiscard]] u64 Time() const;

	void Pause();
	void Resume();

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
