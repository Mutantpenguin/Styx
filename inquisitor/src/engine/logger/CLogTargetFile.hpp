#ifndef CLOGTARGETFILE_HPP
#define CLOGTARGETFILE_HPP

#include <fstream>

#include "CLogger.hpp"

class CLogTargetFile final : public CLogger::CLogTarget
{
	friend class CLogger;

public:
	CLogTargetFile( const CLogger::TLogBuffer &logBuffer, const std::string &directory );
	virtual ~CLogTargetFile( void );

private:
	virtual void Log( const CLogger::logEntry &entry ) override;

	std::ofstream m_log_ofile;
};

#endif // CLOGTARGETFILE_HPP
