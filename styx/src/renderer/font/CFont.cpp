#include "CFont.hpp"

CFont::CFont( const std::string &name, const u16 size, const CSize &atlasSize ) :
	Name { name },
	Size { size },
	AtlasSize { atlasSize }
{}

bool CFont::HasCodepoint( EFontStyle fontStyle, const u32 codepoint ) const
{
	if( fontStyle == EFontStyle::MEDIUM )
	{
		const auto it = CodepointsMedium.find( codepoint );

		if( std::end( CodepointsMedium ) != it )
		{
			return( true );
		}
	}
	else if( fontStyle == EFontStyle::BOLD )
	{
		if( CodepointsBold.has_value() )
		{
			const auto &codepointsBold = CodepointsBold.value();

			const auto it = codepointsBold.find( codepoint );

			if( std::end( codepointsBold ) != it )
			{
				return( true );
			}
		}
	}
	
	return( false );
}

const stbtt_packedchar * CFont::PackedCharFromCodepoint( EFontStyle fontStyle, const u32 codepoint ) const
{
	if( fontStyle == EFontStyle::MEDIUM )
	{
		const auto it = CodepointsMedium.find( codepoint );

		if( std::end( CodepointsMedium ) != it )
		{
			return( &it->second );
		}
	}
	else if( fontStyle == EFontStyle::BOLD )
	{
		if( CodepointsBold.has_value() )
		{
			const auto &codepointsBold = CodepointsBold.value();

			const auto it = codepointsBold.find( codepoint );

			if( std::end( codepointsBold ) != it )
			{
				return( &it->second );
			}
		}
	}
	
	return( nullptr );
}