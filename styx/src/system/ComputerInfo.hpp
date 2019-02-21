#pragma once

#include <string>

#include "src/helper/Types.hpp"

namespace ComputerInfo
{
	std::string	OsName();
	i32			SystemMemoryMiB();
	i32			ProcessorCount();
	std::string	ProcessorInfo();
	std::string	CPUFeatures();
}
