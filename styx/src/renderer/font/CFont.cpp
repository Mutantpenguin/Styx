#include "CFont.hpp"

#include <algorithm>

CFont::CFont()
{
	
}

CFont::~CFont()
{
}

bool CFont::HasCodepoint( const u32 codepoint ) const
{
	const auto it = Codepoints.find( codepoint );
		
	if( std::end( Codepoints ) != it )
	{
		return( true );
	}
	
	return( false );
}

u32 CFont::IndexFromCodepoint( const u32 codepoint ) const
{
	const auto it = Codepoints.find( codepoint );
		
	if( std::end( Codepoints ) != it )
	{
		return( it->second );
	}
	
	return( std::numeric_limits<u32>::max() );
}