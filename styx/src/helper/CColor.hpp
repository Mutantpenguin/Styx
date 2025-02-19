#pragma once

#include <string>

#include "src/core/Types.hpp"

class CColor final
{
public:
	inline CColor()
	{}

	inline CColor& operator= ( const CColor &c )
	{
		m_r = c.m_r;
		m_g = c.m_g;
		m_b = c.m_b;
		m_a = c.m_a;

		return( *this );
	}

	inline CColor( const u32 hexColor ) :
		m_r { static_cast<f16>( ( hexColor >> 16 ) & 0xFF ) / 255.0f },
		m_g { static_cast<f16>( ( hexColor >> 8 ) & 0xFF ) / 255.0f },
		m_b { static_cast<f16>( ( hexColor ) & 0xFF ) / 255.0f },
		m_a { 1.0f }
	{
		clamp();
	}

	inline CColor( const f16 r, const f16 g, const f16 b, const f16 a ) :
		m_r { r },
		m_g { g },
		m_b { b },
		m_a { a }
	{
		clamp();
	}

	inline CColor( const f16 r, const f16 g, const f16 b ) :
		m_r { r },
		m_g { g },
		m_b { b },
		m_a { 1.0f }
	{
		clamp();
	}

	inline CColor( const CColor &c ) :
		m_r { c.m_r },
		m_g { c.m_g },
		m_b { c.m_b },
		m_a { c.m_a }
	{
	}

	inline f16 r() const
	{
		return( m_r );
	}

	inline f16 g() const
	{
		return( m_g );
	}

	inline f16 b() const
	{
		return( m_b );
	}

	inline f16 a() const
	{
		return( m_a );
	}

	std::string rgbHex() const;

protected:
	inline void clamp()
	{
		if( m_r > 1.0f )
		{
			m_r = 1.0f;
		}
		else if( m_r < 0.0f )
		{
			m_r = 0.0f;
		}

		if( m_g > 1.0f )
		{
			m_g = 1.0f;
		}
		else if( m_g < 0.0f )
		{
			m_g = 0.0f;
		}

		if( m_b > 1.0f )
		{
			m_b = 1.0f;
		}
		else if( m_b < 0.0f )
		{
			m_b = 0.0f;
		}

		if( m_a > 1.0f )
		{
			m_a = 1.0f;
		}
		else if( m_a < 0.0f )
		{
			m_a = 0.0f;
		}
	}

	// range 0.0 - 1.0
	f16	m_r { 0.0f };
	f16	m_g { 0.0f };
	f16	m_b { 0.0f };
	f16	m_a { 0.0f };
};

namespace Colors
{
	CColor Aqua();
	CColor Black();
	CColor Blue();
	CColor Brown();
	CColor Cyan();
	CColor Darkblue();
	CColor Fuchsia();
	CColor Green();
	CColor Grey();
	CColor Lightblue();
	CColor Lime();
	CColor Magenta();
	CColor Maroon();
	CColor Navy();
	CColor Olive();
	CColor Orange();
	CColor Purple();
	CColor Red();
	CColor Silver();
	CColor Teal();
	CColor White();
	CColor Yellow();
}

namespace TangoColors
{
	CColor Aluminium();
	CColor AluminiumHighlight();
	CColor AluminiumShadow();
	CColor Butter();
	CColor ButterHighlight();
	CColor ButterShadow();
	CColor Chameleon();
	CColor ChameleonHighlight();
	CColor ChameleonShadow();
	CColor Chocolate();
	CColor ChocolateHighlight();
	CColor ChocolateShadow();
	CColor Orange();
	CColor OrangeHighlight();
	CColor OrangeShadow();
	CColor Plum();
	CColor PlumHighlight();
	CColor PlumShadow();
	CColor ScarletRed();
	CColor ScarletRedHighlight();
	CColor ScarletRedShadow();
	CColor SkyBlue();
	CColor SkyBlueHighlight();
	CColor SkyBlueShadow();
	CColor Slate();
	CColor SlateHighlight();
	CColor SlateShadow();
}