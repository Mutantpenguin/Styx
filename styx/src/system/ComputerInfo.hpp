#pragma once

#include <string>

namespace ComputerInfo
{
	std::string	OsName();
	int			SystemMemoryMiB();
	int			ProcessorCount();
	std::string	ProcessorInfo();
	std::string	CPUFeatures();
}
