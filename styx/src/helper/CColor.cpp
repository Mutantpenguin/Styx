#include "CColor.hpp"

#include "external/fmt/format.h"

std::string CColor::rgbHex() const
{
	const u8 r = static_cast<u8>( std::round( m_r * 255 ) );
	const u8 g = static_cast<u8>( std::round( m_g * 255 ) );
	const u8 b = static_cast<u8>( std::round( m_b * 255 ) );

	return( fmt::format( "{0:02X}{1:02X}{2:02X}", r, g, b ) );
}

namespace Colors
{
	CColor Aqua()
	{
		return( CColor( 0x00FFFF ) );
	}

	CColor Black()
	{
		return( CColor( 0x000000 ) );
	}

	CColor Blue()
	{
		return( CColor( 0x0000FF ) );
	}

	CColor Brown()
	{
		return( CColor( 0xA52A2A ) );
	}

	CColor Cyan()
	{
		return( CColor( 0x00FFFF ) );
	}

	CColor Darkblue()
	{
		return( CColor( 0x0000A0 ) );
	}

	CColor Fuchsia()
	{
		return( CColor( 0xFF00FF ) );
	}

	CColor Green()
	{
		return( CColor( 0x008000 ) );
	}

	CColor Grey()
	{
		return( CColor( 0x808080 ) );
	}

	CColor Lightblue()
	{
		return( CColor( 0xADD8E6 ) );
	}

	CColor Lime()
	{
		return( CColor( 0x00FF00 ) );
	}

	CColor Magenta()
	{
		return( CColor( 0xFF00FF ) );
	}

	CColor Maroon()
	{
		return( CColor( 0x800000 ) );
	}

	CColor Navy()
	{
		return( CColor( 0x000080 ) );
	}

	CColor Olive()
	{
		return( CColor( 0x808000 ) );
	}

	CColor Orange()
	{
		return( CColor( 0xFFA500 ) );
	}

	CColor Purple()
	{
		return( CColor( 0x800080 ) );
	}

	CColor Red()
	{
		return( CColor( 0xFF0000 ) );
	}

	CColor Silver()
	{
		return( CColor( 0xC0C0C0 ) );
	}

	CColor Teal()
	{
		return( CColor( 0x008080 ) );
	}

	CColor White()
	{
		return( CColor( 0xFFFFFF ) );
	}

	CColor Yellow()
	{
		return( CColor( 0xFFFF00 ) );
	}
}