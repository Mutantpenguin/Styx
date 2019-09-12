#include "CFont.hpp"

CFont::CFont( const std::string &name, const u16 size, const CSize &atlasSize ) :
	Name { name },
	Size { size },
	AtlasSize { atlasSize }
{}

bool CFont::HasCodepoint( EFontWeight fontWeight, const u32 codepoint ) const
{
	if( fontWeight == EFontWeight::REGULAR )
	{
		const auto it = CodepointsRegular.find( codepoint );

		if( std::end( CodepointsRegular ) != it )
		{
			return( true );
		}
	}
	else if( fontWeight == EFontWeight::BOLD )
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

const stbtt_packedchar * CFont::PackedCharFromCodepoint( EFontWeight fontWeight, const u32 codepoint ) const
{
	if( fontWeight == EFontWeight::REGULAR )
	{
		const auto it = CodepointsRegular.find( codepoint );

		if( std::end( CodepointsRegular ) != it )
		{
			return( &it->second );
		}
	}
	else if( fontWeight == EFontWeight::BOLD )
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