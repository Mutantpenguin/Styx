#pragma once

#include <string>

#include "src/core/Types.hpp"

enum class EFontStyle : u8
{
	REGULAR,
	BOLD
};

std::string EFontStyleToString( const EFontStyle fontStyle );