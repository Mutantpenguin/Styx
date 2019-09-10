#include "EFontStyle.hpp"

#include "src/core/StyxException.hpp"

std::string EFontStyleToString( const EFontStyle fontStyle )
{
	switch( fontStyle )
	{
	case EFontStyle::REGULAR:
		return( "REGULAR" );

	case EFontStyle::BOLD:
		return( "BOLD" );

	default:
		THROW_STYX_EXCEPTION( "unhandled font style: {0}", static_cast<std::underlying_type<EFontStyle>::type>( fontStyle ) )
	}
}