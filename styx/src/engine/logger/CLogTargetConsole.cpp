#include "CLogTargetConsole.hpp"

#include <iostream>

#include "src/ext/fmt/format.h"
#include "src/ext/fmt/color.h"

#ifdef WIN32
	#include <windows.h>
#endif

CLogTargetConsole::CLogTargetConsole( const CLogger::TLogBuffer & )
{
#ifdef WIN32
	// newer versions of windows console can make use of VT100 control character sequences
	const HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	DWORD dwMode = 0;
	GetConsoleMode( hOut, &dwMode );
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode( hOut, dwMode );
#endif
}

fmt::color GetColor( e_loglevel level )
{
	switch( level )
	{
	case e_loglevel::eERROR:
		return( fmt::color::red );

	case e_loglevel::eWARNING:
		return( fmt::color::yellow );

	case e_loglevel::eINFO:
		return( fmt::color::white );

	case e_loglevel::eDEBUG:
		return( fmt::color::cyan );

	default:
		return( fmt::color::white );
	}
}

void CLogTargetConsole::Log( const std::unique_ptr< const CLogger::logEntry > &entry )
{
	fmt::print( fg( GetColor( entry->m_logLevel ) ), "{0} {1:<9} :  {2}\n", entry->FormattedTime(), "[" + CLogger::LogLevelToString( entry->m_logLevel ) + "]", entry->m_message );
}
