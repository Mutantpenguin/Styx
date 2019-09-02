#include "CFont.hpp"

#include <algorithm>

CFont::CFont()
{
	
}

CFont::~CFont()
{
}

bool CFont::ContainsCodepoint( const u32 codepoint ) const
{
	return( std::find( std::begin( m_codepoints ), std::end( m_codepoints ), codepoint ) != std::end( m_codepoints ) );
}