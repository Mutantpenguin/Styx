#ifndef COMPUTERINFO_HPP
#define COMPUTERINFO_HPP

#include <string>

namespace ComputerInfo
{
	std::string	OsName( void );
	int			SystemMemoryMiB( void );
	int			ProcessorCount( void );
	std::string	ProcessorInfo( void );
	std::string	CPUFeatures( void );
}

#endif // COMPUTERINFO_HPP
