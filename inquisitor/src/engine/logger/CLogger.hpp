#ifndef CLOGGER_HPP
#define CLOGGER_HPP

#include <chrono>
#include <vector>
#include <memory>
#include <list>
#include <sstream>

#include "../../fmt/format.h"

#include "LogHelper.hpp"

#ifdef INQ_DEBUG
	#if 0
		#define LOG( logLevel, ... ) CLogger::CreateLogEntry( logLevel, fmt::format( "{0}:{1}\nFunction: {2}\nMessage: {3}", __FILE__, __LINE__, LogHelper::prettyFunctionNicer( __PRETTY_FUNCTION__ ), fmt::format( __VA_ARGS__ ) ) );
	#else
		#define LOG( logLevel, ... ) CLogger::CreateLogEntry( logLevel, fmt::format( "{0} : {1}",LogHelper::prettyFunctionNicer( __PRETTY_FUNCTION__ ), fmt::format( __VA_ARGS__ ) ) );
	#endif
#else
	#define LOG( logLevel, ... ) CLogger::CreateLogEntry( logLevel, fmt::format( __VA_ARGS__ ) );
#endif

#define logERROR( ... ) LOG( e_loglevel::ERROR, __VA_ARGS__ );
#define logWARNING( ... ) LOG( e_loglevel::WARNING, __VA_ARGS__ );
#define logINFO( ... ) LOG( e_loglevel::INFO, __VA_ARGS__ );

#ifdef INQ_DEBUG
	#define logDEBUG( ... ) LOG( e_loglevel::DEBUG, __VA_ARGS__ );
#else
	#define logDEBUG( ... )
#endif

enum struct e_loglevel : unsigned char
{
	ERROR,
	WARNING,
	INFO,
	DEBUG
};

class CLogger final
{
public:
	static void CreateLogEntry( e_loglevel logLevel, const std::string &message );

	class logEntry final
	{
	public:
		logEntry( const std::chrono::milliseconds &time, e_loglevel loglevel, const std::string &message ) :
			m_time { time },
			m_logLevel { loglevel },
			m_message { message }
		{};

		const std::chrono::milliseconds	m_time;
		const e_loglevel				m_logLevel;
		const std::string				m_message;

		const std::string FormattedTime( void ) const;
	};

	typedef std::vector< std::unique_ptr< logEntry > > TLogBuffer;

	class CLogTarget
	{
		friend class CLogger;

	public:
		virtual ~CLogTarget( void ) {};

	protected:
		virtual void Log( const std::unique_ptr< logEntry > &entry ) = 0;
	};

	template< typename T, typename... Args >
	static void CreateTarget( Args... args )
	{
		m_logTargets.emplace_back( std::make_unique< T >( m_logBuffer, args... ) );
	}

	static void Destroy( void );

	static const std::string LogLevelToString( e_loglevel level );

private:
	CLogger() = delete;
	CLogger( const CLogger& ) = delete;
	CLogger& operator = ( const CLogger& ) = delete;

	~CLogger() = delete;

	static TLogBuffer m_logBuffer;

	static std::list< std::unique_ptr< CLogTarget > > m_logTargets;
};

#endif // CLOGGER_HPP
