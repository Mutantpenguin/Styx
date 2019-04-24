#pragma once

#include <fstream>
#include <filesystem>

#include "src/logger/CLogger.hpp"

class CLogTargetFile final : public CLogger::CLogTarget
{
	friend class CLogger;

public:
	CLogTargetFile( const CLogger::TLogBuffer &logBuffer, const std::filesystem::path &path );
	virtual ~CLogTargetFile();

private:
	virtual void Log( const std::unique_ptr< const CLogger::logEntry > &entry ) override;

	std::ofstream m_log_ofile;
};
