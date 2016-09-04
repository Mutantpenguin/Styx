#include "CLogger.hpp"

#include <chrono>

#include "../../fmt/format.h"

CLogger::TLogBuffer CLogger::m_logBuffer;

std::list< std::unique_ptr< CLogger::CLogTarget > > CLogger::m_logTargets;

const std::string CLogger::errorString		{ "ERROR" };
const std::string CLogger::warningString	{ "WARNING" };
const std::string CLogger::infoString		{ "INFO" };
const std::string CLogger::debugString		{ "DEBUG" };
const std::string CLogger::unknownString	{ "UNKNOWN" };

#ifdef INQ_DEBUG
	e_loglevel CLogger::m_reportingLevel{ logDEBUG };
#else
	e_loglevel CLogger::m_reportingLevel{ logINFO };
#endif


CLogger::~CLogger()
{
	m_logBuffer.emplace_back( new logEntry( m_time_duration, m_lvl, m_output.str() ) );

	for( const std::unique_ptr< CLogTarget > &target : m_logTargets )
	{
		target->Log( *m_logBuffer.back() );
	}
}

void CLogger::SetReportingLevel( e_loglevel level )
{
	m_reportingLevel = level;
}

std::ostringstream& CLogger::Get( const e_loglevel level )
{
	static const std::chrono::high_resolution_clock::time_point first = std::chrono::high_resolution_clock::now();

	const std::chrono::milliseconds	diff	= std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - first );

	const std::chrono::hours		hh		= std::chrono::duration_cast< std::chrono::hours >( diff );
	const std::chrono::minutes		mm		= std::chrono::duration_cast< std::chrono::minutes >( diff % std::chrono::hours( 1 ) );
	const std::chrono::seconds		ss		= std::chrono::duration_cast< std::chrono::seconds >( diff % std::chrono::minutes( 1 ) );
	const std::chrono::milliseconds	msec	= std::chrono::duration_cast< std::chrono::milliseconds >( diff % std::chrono::seconds( 1 ) );

	m_time_duration = fmt::format( "{:02d}:{:02d}:{:02d}.{:03d}", hh.count(), mm.count(), ss.count(), msec.count() );

	m_lvl = level;

	return( m_output );
}

const std::string &CLogger::ToString( e_loglevel level )
{
	switch( level )
	{
		case e_loglevel::ERROR :
			return( errorString );

		case e_loglevel::WARNING :
			return( warningString );

		case e_loglevel::INFO :
			return( infoString );

		case e_loglevel::DEBUG :
			return( debugString );

		default:
			return( unknownString );
	}
}

e_loglevel CLogger::FromString( const std::string& level )
{
	if( level == debugString )
	{
		return( e_loglevel::DEBUG );
	}
	else if( level == infoString )
	{
		return( e_loglevel::INFO );
	}
	else if( level == warningString )
	{
		return( e_loglevel::WARNING );
	}
	else if( level == errorString )
	{
		return( e_loglevel::ERROR );
	}

	CLogger().Get( logWARNING ) << "Unknown logging level '" << level << "'. Using '" << ToString( e_loglevel::INFO ) << "' as default.";
	return( e_loglevel::INFO );
}

void CLogger::Destroy( void )
{
	for( CLogger::logEntry *entry : m_logBuffer )
	{
		delete entry;
	}
	m_logBuffer.clear();
}
