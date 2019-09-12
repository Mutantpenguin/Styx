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

namespace TangoColors
{
	CColor Aluminium()
	{
		return( CColor( 0xD3D7CF ) );
	}

	CColor AluminiumHighlight()
	{
		return( CColor( 0xEEEEEC ) );
	}

	CColor AluminiumShadow()
	{
		return( CColor( 0xBABDB6 ) );
	}

	CColor Butter()
	{
		return( CColor( 0xEDD400 ) );
	}

	CColor ButterHighlight()
	{
		return( CColor( 0xFCE94F ) );
	}

	CColor ButterShadow()
	{
		return( CColor( 0xC4A000 ) );
	}

	CColor Chameleon()
	{
		return( CColor( 0x73D216 ) );
	}

	CColor ChameleonHighlight()
	{
		return( CColor( 0x8AE234 ) );
	}

	CColor ChameleonShadow()
	{
		return( CColor( 0x4E9A06 ) );
	}

	CColor Chocolate()
	{
		return( CColor( 0xC17D11 ) );
	}

	CColor ChocolateHighlight()
	{
		return( CColor( 0xE9B96E ) );
	}

	CColor ChocolateShadow()
	{
		return( CColor( 0x8F5902 ) );
	}

	CColor Orange()
	{
		return( CColor( 0xF57900 ) );
	}

	CColor OrangeHighlight()
	{
		return( CColor( 0xFCAF3E ) );
	}

	CColor OrangeShadow()
	{
		return( CColor( 0xCE5C00 ) );
	}

	CColor Plum()
	{
		return( CColor( 0x75507B ) );
	}

	CColor PlumHighlight()
	{
		return( CColor( 0xAD7FA8 ) );
	}

	CColor PlumShadow()
	{
		return( CColor( 0x5C3566 ) );
	}

	CColor ScarletRed()
	{
		return( CColor( 0xCC0000 ) );
	}

	CColor ScarletRedHighlight()
	{
		return( CColor( 0xEF2929 ) );
	}

	CColor ScarletRedShadow()
	{
		return( CColor( 0xA40000 ) );
	}

	CColor SkyBlue()
	{
		return( CColor( 0x3465A4 ) );
	}

	CColor SkyBlueHighlight()
	{
		return( CColor( 0x729FCF ) );
	}

	CColor SkyBlueShadow()
	{
		return( CColor( 0x204A87 ) );
	}

	CColor Slate()
	{
		return( CColor( 0x555753 ) );
	}

	CColor SlateHighlight()
	{
		return( CColor( 0x888A85 ) );
	}

	CColor SlateShadow()
	{
		return( CColor( 0x2E3436 ) );
	}
}