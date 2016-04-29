#ifndef CLOGGER_HPP
#define CLOGGER_HPP


#include <vector>
#include <memory>
#include <list>
#include <sstream>

#include "LogHelper.hpp"

#ifdef INQ_DEBUG
	#if 0
		#define LOG( level )	if( level > CLogger::ReportingLevel() ) \
									; \
								else \
									CLogger().Get( level ) << __FILE__ << ":" << __LINE__ << std::endl << "Function: " << LogHelper::prettyFunctionNicer( __PRETTY_FUNCTION__ ) << std::endl << "Message: "
	#else
		#define LOG( level )	if( level > CLogger::ReportingLevel() ) \
									; \
								else \
									CLogger().Get( level ) << LogHelper::prettyFunctionNicer( __PRETTY_FUNCTION__ ) << " : "
	#endif
#else
	#define LOG( level ) if( level > CLogger::ReportingLevel() ) \
								; \
							else \
								CLogger().Get( level )
#endif

enum struct e_loglevel : unsigned char
{
	ERROR,
	WARNING,
	INFO,
	DEBUG
};

#define logERROR	e_loglevel::ERROR
#define logWARNING	e_loglevel::WARNING
#define logINFO		e_loglevel::INFO
#define logDEBUG	e_loglevel::DEBUG

class CLogger final
{
public:
	struct logEntry final
	{
		logEntry( const std::string &time, e_loglevel loglevel, const std::string &message ) :
			m_time( time ),
			m_logLevel( loglevel ),
			m_message( message )
		{};

		const std::string	m_time;
		const e_loglevel	m_logLevel;
		const std::string	m_message;
	};

	typedef std::vector< logEntry* > TLogBuffer;

	class CLogTarget
	{
		friend class CLogger;

	public:
		virtual ~CLogTarget( void ) {};

	protected:
		virtual void Log( const logEntry &entry ) = 0;
	};

	CLogger() {};
	~CLogger();

	std::ostringstream& Get( const e_loglevel level );

	static void Destroy( void );

	template< typename T, typename... Args >
	static void CreateTarget( Args... args )
	{
		m_logTargets.emplace_back( std::make_unique< T >( m_logBuffer, args... ) );
	}

	inline static e_loglevel& ReportingLevel( void )
	{
		return( m_reportingLevel );
	}

	static void SetReportingLevel( e_loglevel level );

	static const std::string	&ToString( e_loglevel level );
	static e_loglevel			FromString( const std::string& level );

private:
	static e_loglevel m_reportingLevel;

	std::ostringstream	m_output;
	e_loglevel			m_lvl { logDEBUG };
	std::string			m_time_duration;

	static TLogBuffer m_logBuffer;

	static std::list< std::unique_ptr< CLogTarget > > m_logTargets;

	CLogger( const CLogger& );
	CLogger& operator =(const CLogger&);

	static const std::string errorString;
	static const std::string warningString;
	static const std::string infoString;
	static const std::string debugString;
	static const std::string unknownString;
};

#endif // CLOGGER_HPP
