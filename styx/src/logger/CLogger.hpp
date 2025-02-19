#pragma once

#include <chrono>
#include <vector>
#include <memory>
#include <list>
#include <sstream>

#include "external/fmt/format.h"

#include "src/core/Types.hpp"

#include "src/logger/LogHelper.hpp"

#ifdef STYX_DEBUG
	#ifdef __linux__
		#if 0
			#define LOG( logLevel, ... ) CLogger::Log( logLevel, fmt::format( "{0}:{1}\nFunction: {2}\nMessage: {3}", __FILE__, __LINE__, LogHelper::prettyFunctionNicer( __PRETTY_FUNCTION__ ), fmt::format( __VA_ARGS__ ) ) );
		#else
			#define LOG( logLevel, ... ) CLogger::Log( logLevel, fmt::format( "{0} : {1}", LogHelper::prettyFunctionNicer( __PRETTY_FUNCTION__ ), fmt::format( __VA_ARGS__ ) ) );
		#endif
	#elif _WIN32
		#if 0
			#define LOG( logLevel, ... ) CLogger::Log( logLevel, fmt::format( "{0}:{1}\nFunction: {2}\nMessage: {3}", __FILE__, __LINE__, __FUNCTION__, fmt::format( __VA_ARGS__ ) ) );
		#else
			#define LOG( logLevel, ... ) CLogger::Log( logLevel, fmt::format( "{0} : {1}", __FUNCTION__, fmt::format( __VA_ARGS__ ) ) );
		#endif
	#else
		#error "unsupported platform"
	#endif
#else
	#define LOG( logLevel, ... ) CLogger::Log( logLevel, fmt::format( __VA_ARGS__ ) );
#endif

#define logERROR( ... ) LOG( e_loglevel::eERROR, __VA_ARGS__ );
#define logWARNING( ... ) LOG( e_loglevel::eWARNING, __VA_ARGS__ );
#define logINFO( ... ) LOG( e_loglevel::eINFO, __VA_ARGS__ );

#ifdef STYX_DEBUG
	#define logDEBUG( ... ) LOG( e_loglevel::eDEBUG, __VA_ARGS__ );
#else
	#define logDEBUG( ... )
#endif

enum struct e_loglevel : u8
{
	eERROR,
	eWARNING,
	eINFO,
	eDEBUG
};

class CLogger final
{
public:
	static void Log( e_loglevel logLevel, const std::string &message );

	class CLogEntry final
	{
	public:
		CLogEntry( const std::chrono::milliseconds &time, e_loglevel loglevel, const std::string &message ) :
			m_time { time },
			m_logLevel { loglevel },
			m_message { message }
		{};

		const std::chrono::milliseconds	m_time;
		const e_loglevel				m_logLevel;
		const std::string				m_message;

		const std::string FormattedTime() const;
	};

	using TLogBuffer = std::vector<std::unique_ptr<const CLogEntry>>;

	class CLogTarget
	{
		friend class CLogger;

	public:
		virtual ~CLogTarget() {};

	protected:
		virtual void Log( const std::unique_ptr<const CLogEntry> &entry ) = 0;
	};

	template<typename T, typename... Args>
	static void CreateTarget( Args... args )
	{
		static_assert( std::is_base_of<CLogTarget, T>::value, "must derive from CLogTarget" );

		m_logTargets.emplace_back( std::make_unique<T>( m_logBuffer, args... ) );
	}

	static void Destroy();

	static const std::string LogLevelToString( e_loglevel level );

private:
	CLogger() = delete;
	CLogger( const CLogger& ) = delete;
	CLogger& operator = ( const CLogger& ) = delete;

	~CLogger() = delete;

	static TLogBuffer m_logBuffer;

	static std::list<std::unique_ptr<CLogTarget>> m_logTargets;
};
