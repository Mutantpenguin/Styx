#ifndef ALHELPER_HPP
#define ALHELPER_HPP

#include <string>

#include <AL/al.h>

namespace ALHelper
{
	std::string GetOpenALErrorString( const ALenum error );
}

#endif // ALHELPER_HPP
