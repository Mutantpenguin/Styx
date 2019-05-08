#pragma once

#include "src/logger/CLogger.hpp"

class CLogTargetMessageBox final : public CLogger::CLogTarget
{
	friend class CLogger;

public:
	explicit CLogTargetMessageBox( const CLogger::TLogBuffer & ) {};

private:
	virtual void Log( const std::unique_ptr<const CLogger::CLogEntry> &entry ) override;
};
