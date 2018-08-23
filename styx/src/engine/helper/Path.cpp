#include "Path.hpp"

namespace Path
{
	std::string Extension( const std::string &path )
	{
		return( path.substr( path.find_first_of( "." ) + 1 ) );
	}
	
	std::string Directory( const std::string &path )
	{
		return( path.substr( 0, path.find_last_of( "/" ) + 1 ) );
	}
	
	std::string Name( const std::string &path )
	{
		return( path.substr( path.find_last_of( "/" ) + 1 ) );
	}
};