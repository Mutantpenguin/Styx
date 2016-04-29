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
		( "loglvl", po::value< std::string >(), "logging level" ) // TODO somehow define all possible values
		( "logToMsgBox", "show a message-box for errors" );

	cmdline_options.add( generic );
	cmdline_options.add( config );

	try
	{
	    po::store( po::parse_command_line( argc, argv, cmdline_options ), vm );
	}
	catch( std::exception &e )
	{
		LOG( logERROR ) << "failed to parse the command-line options: " << e.what();
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
		LOG( logERROR ) << e.what();
		return( EXIT_FAILURE );
	}

	if( vm.count( "logToMsgBox" ) )
	{
		CLogger::CreateTarget< CLogTargetMessageBox >();
	}

	LOG( logINFO ) << "starting " << CEngine::GetVersionString();

	if( vm.count( "loglvl" ) )
	{
		CLogger::SetReportingLevel( CLogger::FromString( vm[ "loglvl" ].as< std::string >() ) );
	}

	LOG( logINFO ) << "logging-level is '" << CLogger::ToString( CLogger::ReportingLevel() ) << "'";

	// get some information about the system we are running on
	LOG( logINFO ) << "Operating System    : " << ComputerInfo::OsName();
	LOG( logINFO ) << "Processor Info      : " << ComputerInfo::ProcessorInfo();
	LOG( logINFO ) << "Processor Count     : " << ComputerInfo::ProcessorCount();
	LOG( logINFO ) << "Processor Features  : " << ComputerInfo::CPUFeatures();
	LOG( logINFO ) << "System Memory Total : " << ComputerInfo::SystemMemoryMiB() << "MiB";

	try
	{
		CEngine engine( argv[ 0 ], gameDirectory, settingsFile );

		engine.Run();
	}
	catch( ... )
	{
		LOG( logERROR ) << "unable to run the game";

		return( EXIT_FAILURE );
	}

	return( EXIT_SUCCESS );
}
