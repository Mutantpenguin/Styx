#pragma once

#include <string>

#include "src/core/Types.hpp"

enum class EFontWeight : u8
{
	REGULAR,
	BOLD
};

std::string EFontWeightToString( const EFontWeight fontWeight );