#include "CLogTargetConsole.hpp"

#include <iostream>

#include "src/ext/fmt/format.h"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	// TODO still needed? #define WINVER 0x0501
	#include <windows.h>
#endif

#ifndef WIN32
	#define COLOR_INFO		"\033[37m"
	#define COLOR_ERROR		"\033[31m"
	#define COLOR_WARNING	"\033[33m"
	#define COLOR_DEBUG		"\033[36m"
	#define COLOR_NORMAL	"\033[0m"
#else
	#define COLOR_INFO      15
	#define COLOR_ERROR     12
	#define COLOR_WARNING   14
	#define COLOR_DEBUG     11
	#define COLOR_NORMAL    7
#endif

void CLogTargetConsole::Log( const std::unique_ptr< CLogger::logEntry > &entry )
{
	std::cout << entry->FormattedTime() << " ";

	SetColor( GetColor( entry->m_logLevel ) );

	std::cout << fmt::format( "{0:<9}", "[" + CLogger::LogLevelToString( entry->m_logLevel ) + "]" );

	SetColor( COLOR_NORMAL );

	std::cout << " : " << entry->m_message << std::endl;
}

#ifndef WIN32
	std::string CLogTargetConsole::GetColor( e_loglevel level ) const
#else
	int CLogTargetConsole::GetColor( e_loglevel level ) const
#endif
	{
		switch( level )
		{
			case e_loglevel::ERROR :
				return( COLOR_ERROR );

			case e_loglevel::WARNING :
				return( COLOR_WARNING );

			case e_loglevel::INFO :
				return( COLOR_INFO );

			case e_loglevel::DEBUG :
				return( COLOR_DEBUG );

			default:
				return( COLOR_NORMAL );
		}
	}

#ifndef WIN32
	void CLogTargetConsole::SetColor( const std::string &color ) const
	{
		std::cout << color;
	}
#else
	void CLogTargetConsole::SetColor( const int &color ) const
	{
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
	}
#endif
