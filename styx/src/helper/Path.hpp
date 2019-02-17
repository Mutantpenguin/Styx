#pragma once

#include <string>

namespace Path
{
	std::string Extension( const std::string &path );
	std::string Directory( const std::string &path );
	std::string Name( const std::string &path );
};

