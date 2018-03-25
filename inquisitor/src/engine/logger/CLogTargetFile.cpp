#include "CLogTargetFile.hpp"

#include <iostream>

#include "src/ext/fmt/time.h"

#include "src/engine/helper/Date.hpp"

#include "src/ext/fmt/format.h"

CLogTargetFile::CLogTargetFile( const CLogger::TLogBuffer &logBuffer, const std::string &directory ) :
	m_log_ofile( ( fmt::format("{0}{1:%Y-%m-%d_%H-%M-%S}.log", directory, fmt::localtime( Date::GetCurrentDateTime() ) ) ).c_str(), std::ios::out | std::ios::app )
{
	// write the whole buffer to disk
	for( const std::unique_ptr< const CLogger::logEntry > &entry : logBuffer )
	{
		Log( entry );
	}
}

CLogTargetFile::~CLogTargetFile( void )
{
	m_log_ofile.flush();
	m_log_ofile.close();
}

void CLogTargetFile::Log( const std::unique_ptr< const CLogger::logEntry > &entry )
{
	m_log_ofile << entry->FormattedTime() << " " << fmt::format( "{0:<9} : {1}\n", "[" + CLogger::LogLevelToString( entry->m_logLevel ) + "]", entry->m_message );

	#ifdef INQ_DEBUG
		m_log_ofile.flush();
	#endif
}
