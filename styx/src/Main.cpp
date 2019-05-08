#include <iostream>

// explicitly include SDL2.h so it can do its thing with SDL_main
#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "external/CLI11/CLI11.hpp"

#include "src/logger/CLogger.hpp"
#include "src/logger/CLogTargetConsole.hpp"
#include "src/logger/CLogTargetMessageBox.hpp"

#include "src/system/ComputerInfo.hpp"
#include "src/system/CEngine.hpp"

#include "src/core/StyxException.hpp"

int main( int argc, char *argv[] )
{
	std::atexit( CLogger::Destroy );

	CLogger::CreateTarget<CLogTargetConsole>();

	std::string gameDirectoryString;
	std::string settingsFile;

	CLI::App app { CEngine::GetVersionString() };

	app.add_option( "-g", gameDirectoryString, "path to the directory of the game" )
		->check( CLI::ExistingDirectory );

	app.add_option( "-s", settingsFile, "path to a settings-file" )
		->check( CLI::ExistingFile );

	const auto logErrorsToMsgBoxOption = app.add_flag( "-l", "show a message-box for errors" );

	const auto showVersionOption = app.add_flag( "-v", "produce version string" );

	try
	{
		app.parse( argc, argv );
	}
	catch( const CLI::ParseError &e )
	{
		logERROR( "unable to parse command line options: {0}", e.what() );
		return( app.exit( e ) );
	}

	if( showVersionOption->count() > 0 )
	{
		fmt::print( CEngine::GetVersionString() );
		return( EXIT_SUCCESS );
	}

	if( logErrorsToMsgBoxOption->count() > 0 )
	{
		CLogger::CreateTarget<CLogTargetMessageBox>();
	}


	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "starting {0}", CEngine::GetVersionString() );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	// get some information about the system we are running on
	logINFO( "Operating System    : {0}",     ComputerInfo::OsName() );
	logINFO( "Processor Info      : {0}",     ComputerInfo::ProcessorInfo() );
	logINFO( "Processor Count     : {0}",     ComputerInfo::ProcessorCount() );
	logINFO( "Processor Features  : {0}",     ComputerInfo::CPUFeatures() );
	logINFO( "System Memory Total : {0} MiB", ComputerInfo::SystemMemoryMiB() );

	logINFO( "" );

	try
	{
		CEngine engine( argv[ 0 ], gameDirectoryString, settingsFile );

		engine.Run();
	}
	catch( const styx_internal::StyxException &e )
	{
		logERROR( "unable to run the game:\nfile '{0}' on line {1}\nfunction '{2}'\n{3}", e.File(), e.Line(), e.Func() ,e.what() );

		return( EXIT_FAILURE );
	}
	catch( const std::exception &e )
	{
		logERROR( "unable to run the game:\n{0}", e.what() );

		return( EXIT_FAILURE );
	}
	catch( ... )
	{
		logERROR( "unable to run the game because of unknown reason" );

		return( EXIT_FAILURE );
	}

	return( EXIT_SUCCESS );
}
