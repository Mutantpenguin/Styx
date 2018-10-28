#pragma once

#include <string>

#include <AL/al.h>

namespace ALHelper
{
	std::string GetOpenALErrorString( const ALenum error );
}
