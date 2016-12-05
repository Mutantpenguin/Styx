#include "CLogTargetFile.hpp"

#include <iostream>

#include "src/engine/helper/Date.hpp"

#include "src/ext/fmt/format.h"


CLogTargetFile::CLogTargetFile( const CLogger::TLogBuffer &logBuffer, const std::string &directory ) :
	m_log_ofile( ( directory + Date::GetCurrentDateString() + ".log" ).c_str(), std::ios::out | std::ios::app )
{
	// write the whole buffer to disk
	for( const std::unique_ptr< CLogger::logEntry > &entry : logBuffer )
	{
		Log( entry );
	}
}

CLogTargetFile::~CLogTargetFile( void )
{
	m_log_ofile.flush();
	m_log_ofile.close();
}

void CLogTargetFile::Log( const std::unique_ptr< CLogger::logEntry > &entry )
{
	m_log_ofile << entry->FormattedTime() << " " << fmt::format( "{0:<9} : {1}\n", "[" + CLogger::LogLevelToString( entry->m_logLevel ) + "]", entry->m_message );

	#ifdef INQ_DEBUG
		m_log_ofile.flush();
	#endif
}
