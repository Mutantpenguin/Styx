#include "CColor.hpp"

#include "external/fmt/format.h"

std::string CColor::rgbHex() const
{
	const u8 r = static_cast<u8>( std::round( m_r * 255 ) );
	const u8 g = static_cast<u8>( std::round( m_g * 255 ) );
	const u8 b = static_cast<u8>( std::round( m_b * 255 ) );

	return( fmt::format( "{0:02X}{1:02X}{2:02X}", r, g, b ) );
}