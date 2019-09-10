#include "CFont.hpp"

CFont::CFont( const std::string &name, const u16 size, const CSize &atlasSize ) :
	Name { name },
	Size { size },
	AtlasSize { atlasSize }
{}

bool CFont::HasCodepoint( EFontStyle fontStyle, const u32 codepoint ) const
{
	if( fontStyle == EFontStyle::REGULAR )
	{
		const auto it = CodepointsRegularStyle.find( codepoint );

		if( std::end( CodepointsRegularStyle ) != it )
		{
			return( true );
		}
	}
	else if( fontStyle == EFontStyle::BOLD )
	{
		if( CodepointsBoldStyle.has_value() )
		{
			const auto &codepointsBoldStyle = CodepointsBoldStyle.value();

			const auto it = codepointsBoldStyle.find( codepoint );

			if( std::end( codepointsBoldStyle ) != it )
			{
				return( true );
			}
		}
	}
	
	return( false );
}

const stbtt_packedchar * CFont::PackedCharFromCodepoint( EFontStyle fontStyle, const u32 codepoint ) const
{
	if( fontStyle == EFontStyle::REGULAR )
	{
		const auto it = CodepointsRegularStyle.find( codepoint );

		if( std::end( CodepointsRegularStyle ) != it )
		{
			return( &it->second );
		}
	}
	else if( fontStyle == EFontStyle::BOLD )
	{
		if( CodepointsBoldStyle.has_value() )
		{
			const auto &codepointsBoldStyle = CodepointsBoldStyle.value();

			const auto it = codepointsBoldStyle.find( codepoint );

			if( std::end( codepointsBoldStyle ) != it )
			{
				return( &it->second );
			}
		}
	}
	
	return( nullptr );
}