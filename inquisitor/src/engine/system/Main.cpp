#include <iostream>

// explicitly include SDL2.h so it can do its thing with SDL_main
#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/ext/CLI11/CLI11.hpp"

#include "src/engine/logger/CLogger.hpp"
#include "src/engine/logger/CLogTargetConsole.hpp"
#include "src/engine/logger/CLogTargetMessageBox.hpp"

#include "CEngine.hpp"
#include "CFileSystem.hpp"
#include "CGameInfo.hpp"
#include "ComputerInfo.hpp"
#include "CSettings.hpp"

int main( int argc, char *argv[] )
{
	std::atexit( CLogger::Destroy );

	CLogger::CreateTarget< CLogTargetConsole >();

	std::string gameDirectory;
	std::string settingsFile;

	CLI::App app { CEngine::GetVersionString() };

	app.add_option( "--gameDirectory,-g", gameDirectory, "directory of the game" )
		->check( CLI::ExistingDirectory );

	app.add_option( "--settingsFile,-s", settingsFile, "path to a settings-file" )
		->check( CLI::ExistingFile );

	const auto logErrorsToMsgBoxOption = app.add_flag( "-l,--logErrorsToMsgBox", "show a message-box for errors" );

	const auto showVersionOption = app.add_flag( "-v,--version", "produce version string" );

	try
	{
		app.parse( argc, argv );
	}
	catch( const CLI::ParseError &e )
	{
		return( app.exit( e ) );
	}

	if( showVersionOption->count() > 0 )
	{
		std::cout << CEngine::GetVersionString() << std::endl;
		return( EXIT_SUCCESS );
	}

	if( logErrorsToMsgBoxOption->count() > 0 )
	{
		CLogger::CreateTarget< CLogTargetMessageBox >();
	}


	logINFO( "--------------------------------------------------------------------------------" );
	logINFO( "starting {0}", CEngine::GetVersionString() );
	logINFO( "--------------------------------------------------------------------------------" );

	logINFO( "" );

	// get some information about the system we are running on
	logINFO( "Operating System    : {0}",    ComputerInfo::OsName() );
	logINFO( "Processor Info      : {0}",    ComputerInfo::ProcessorInfo() );
	logINFO( "Processor Count     : {0}",    ComputerInfo::ProcessorCount() );
	logINFO( "Processor Features  : {0}",    ComputerInfo::CPUFeatures() );
	logINFO( "System Memory Total : {0}MiB", ComputerInfo::SystemMemoryMiB() );

	logINFO( "" );

	try
	{
		CEngine engine( argv[ 0 ], gameDirectory, settingsFile );

		engine.Run();
	}
	catch( std::exception &e )
	{
		logERROR( "unable to run the game: {0}", e.what() );

		return( EXIT_FAILURE );
	}

	return( EXIT_SUCCESS );
}
