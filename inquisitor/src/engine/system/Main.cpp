#include <iostream>

#include <boost/program_options.hpp>

#include "../logger/CLogger.hpp"
#include "../logger/CLogTargetConsole.hpp"
#include "../logger/CLogTargetMessageBox.hpp"

#include "CEngine.hpp"
#include "CFileSystem.hpp"
#include "CGameInfo.hpp"
#include "ComputerInfo.hpp"
#include "CSettings.hpp"

int main( int argc, char *argv[] )
{
	std::atexit( CLogger::Destroy );

	CLogger::CreateTarget< CLogTargetConsole >();

	namespace po = boost::program_options;

	po::options_description  generic( "Generic options" );
	po::options_description  config( "Configuration" );
	po::options_description  cmdline_options;
	po::variables_map        vm;

	std::string settingsFile;

	generic.add_options()
		( "version,v", "produce version string" )
		( "help,h",    "produce help message" );

	std::string gameDirectory;

	config.add_options()
		( "gameDirectory", po::value< std::string >( &gameDirectory )->required(), "directory of the game" )
		( "settingsFile", po::value< std::string >( &settingsFile ), "name of a settings-file" )
		( "logToMsgBox", "show a message-box for errors" );

	cmdline_options.add( generic );
	cmdline_options.add( config );

	try
	{
	    po::store( po::parse_command_line( argc, argv, cmdline_options ), vm );
	}
	catch( std::exception &e )
	{
		logERROR( "failed to parse the command-line options: {0}", e.what() );
		return( EXIT_FAILURE );
	}

	if( vm.count( "help" ) )
	{
		std::cout << cmdline_options << std::endl;
		return( EXIT_SUCCESS );
	}

	if( vm.count( "version" ) )
	{
		std::cout << CEngine::GetVersionString() << std::endl;
		return( EXIT_SUCCESS );
	}

	try
	{
		po::notify( vm );
	}
	catch( std::exception &e )
	{
		logERROR( e.what() );
		return( EXIT_FAILURE );
	}

	if( vm.count( "logToMsgBox" ) )
	{
		CLogger::CreateTarget< CLogTargetMessageBox >();
	}

	logINFO( "starting {0}", CEngine::GetVersionString() );

	// get some information about the system we are running on
	logINFO( "Operating System    : {0}",    ComputerInfo::OsName() );
	logINFO( "Processor Info      : {0}",    ComputerInfo::ProcessorInfo() );
	logINFO( "Processor Count     : {0}",    ComputerInfo::ProcessorCount() );
	logINFO( "Processor Features  : {0}",    ComputerInfo::CPUFeatures() );
	logINFO( "System Memory Total : {0}MiB", ComputerInfo::SystemMemoryMiB() );

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
