#include "EFontWeight.hpp"

#include "src/core/StyxException.hpp"

std::string EFontWeightToString( const EFontWeight fontWeight )
{
	switch( fontWeight )
	{
	case EFontWeight::REGULAR:
		return( "REGULAR" );

	case EFontWeight::BOLD:
		return( "BOLD" );

	default:
		THROW_STYX_EXCEPTION( "unhandled font weight: {0}", static_cast<std::underlying_type<EFontWeight>::type>( fontWeight ) )
	}
}