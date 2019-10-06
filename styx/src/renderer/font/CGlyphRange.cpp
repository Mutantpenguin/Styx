#include "CGlyphRange.hpp"

CGlyphRange::CGlyphRange( const u32 from, const u32 to )
{
	Add( from, to );
}

void CGlyphRange::Add( const u32 from, const u32 to )
{
	m_ranges.emplace_back( from, to );
}

void CGlyphRange::AddDefault()
{
	Add( 0x0020, 0x007F ); // Basic Latin
	Add( 0x00A0, 0x00FF ); // Latin-1 Supplement
}

std::vector<i32> CGlyphRange::ToVector() const
{
	std::vector<i32> glyphs;
	
	for( const auto [ from, to ] : m_ranges )
	{
		for( i32 i = from; i <= to; i++ )
		{
			glyphs.emplace_back( i );
		}
	}
	
	return( glyphs );
}

u32 CGlyphRange::Count() const
{
	u32 count = 0;

	for( const auto[ from, to ] : m_ranges )
	{
		count += to - from + 1;
	}

	return( count );
}

CGlyphRange CGlyphRange::Default()
{
	CGlyphRange defaultGlyphrange;

	defaultGlyphrange.AddDefault();

	return( defaultGlyphrange );
}