#include "CLogger.hpp"

CLogger::TLogBuffer CLogger::m_logBuffer;

std::list< std::unique_ptr< CLogger::CLogTarget > > CLogger::m_logTargets;

void CLogger::Log( e_loglevel logLevel, const std::string &message )
{
	static const std::chrono::high_resolution_clock::time_point first = std::chrono::high_resolution_clock::now();

	const std::chrono::milliseconds	diff = std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - first );

	m_logBuffer.emplace_back( std::make_unique< logEntry >( diff, logLevel, message ) );

	for( const std::unique_ptr< CLogTarget > &target : m_logTargets )
	{
		target->Log( m_logBuffer.back() );
	}
}

const std::string CLogger::LogLevelToString( e_loglevel level )
{
	switch( level )
	{
		case e_loglevel::ERROR :
			return( "ERROR" );

		case e_loglevel::WARNING :
			return( "WARNING" );

		case e_loglevel::INFO :
			return( "INFO" );

		case e_loglevel::DEBUG :
			return( "DEBUG" );

		default:
			return( "UNKNOWN" );
	}
}

void CLogger::Destroy( void )
{
	m_logBuffer.clear();
}

const std::string CLogger::logEntry::FormattedTime( void ) const
{
	const std::chrono::hours		hh		= std::chrono::duration_cast< std::chrono::hours >( m_time );
	const std::chrono::minutes		mm		= std::chrono::duration_cast< std::chrono::minutes >( m_time % std::chrono::hours( 1 ) );
	const std::chrono::seconds		ss		= std::chrono::duration_cast< std::chrono::seconds >( m_time % std::chrono::minutes( 1 ) );
	const std::chrono::milliseconds	msec	= std::chrono::duration_cast< std::chrono::milliseconds >( m_time % std::chrono::seconds( 1 ) );

	return( fmt::format( "{:02d}:{:02d}:{:02d}.{:03d}", hh.count(), mm.count(), ss.count(), msec.count() ) );
}
