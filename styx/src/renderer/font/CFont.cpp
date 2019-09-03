#include "CFont.hpp"

bool CFont::HasCodepoint( const u32 codepoint ) const
{
	const auto it = Codepoints.find( codepoint );
		
	if( std::end( Codepoints ) != it )
	{
		return( true );
	}
	
	return( false );
}

const stbtt_packedchar * CFont::PackedCharFromCodepoint( const u32 codepoint ) const
{
	const auto it = Codepoints.find( codepoint );
		
	if( std::end( Codepoints ) != it )
	{
		return( &it->second );
	}
	
	return( nullptr );
}