#include "CLogTargetFile.hpp"

#include <boost/format.hpp>

#include "../helper/Date.hpp"


CLogTargetFile::CLogTargetFile( const CLogger::TLogBuffer &logBuffer, const std::string &directory ) :
	m_log_ofile( ( directory + Date::GetCurrentDateString() + ".log" ).c_str(), std::ios::out | std::ios::app )
{
	// write the whole buffer to disk
	for( const CLogger::logEntry *entry : logBuffer )
	{
		Log( *entry );
	}
}

CLogTargetFile::~CLogTargetFile( void )
{
	m_log_ofile.flush();
	m_log_ofile.close();
}

void CLogTargetFile::Log( const CLogger::logEntry &entry )
{
	m_log_ofile << entry.m_time << " " + boost::str( boost::format( "%-9s" ) % ( "[" + CLogger::ToString( entry.m_logLevel ) + "]" ) ) + " : " << entry.m_message << std::endl;

	#ifdef INQ_DEBUG
		m_log_ofile.flush();
	#endif
}
