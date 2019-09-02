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
	const auto it = m_codepoints.find( codepoint );
		
	if( std::end( m_codepoints ) != it )
	{
		return( true );
	}
	
	return( false );
}

u32 CFont::IndexFromCodepoint( const u32 codepoint ) const
{
	return( m_codepoints.at( codepoint ) );
}