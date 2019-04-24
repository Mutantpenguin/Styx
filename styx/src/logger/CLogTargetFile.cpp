#include "CLogTargetFile.hpp"

#include <iostream>

#include "external/fmt/time.h"

#include "src/helper/Date.hpp"

#include "external/fmt/format.h"

CLogTargetFile::CLogTargetFile( const CLogger::TLogBuffer &logBuffer, const std::filesystem::path &path ) :
	m_log_ofile( path / fmt::format("{0:%Y-%m-%d_%H-%M-%S}.log", fmt::localtime( Date::GetCurrentDateTime() ) ), std::ios::out | std::ios::app )
{
	// write the whole buffer to disk
	for( const std::unique_ptr< const CLogger::logEntry > &entry : logBuffer )
	{
		Log( entry );
	}
}

CLogTargetFile::~CLogTargetFile()
{
	m_log_ofile.flush();
	m_log_ofile.close();
}

void CLogTargetFile::Log( const std::unique_ptr< const CLogger::logEntry > &entry )
{
	m_log_ofile << entry->FormattedTime() << " " << fmt::format( "{0:<9} : {1}\n", "[" + CLogger::LogLevelToString( entry->m_logLevel ) + "]", entry->m_message );

	#ifdef STYX_DEBUG
		m_log_ofile.flush();
	#endif
}
