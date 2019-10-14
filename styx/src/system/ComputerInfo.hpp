#pragma once

#include <string>

#include "src/core/Types.hpp"

namespace ComputerInfo
{
	std::string	OsName();
	s32			SystemMemoryMiB();
	s32			ProcessorCount();
	std::string	ProcessorInfo();
	std::string	CPUFeatures();
}
