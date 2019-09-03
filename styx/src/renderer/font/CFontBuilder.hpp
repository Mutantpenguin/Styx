#pragma once

#include <memory>

#include "src/system/CFileSystem.hpp"

#include "src/renderer/font/CFont.hpp"

#include "src/renderer/font/CGlyphRanges.hpp"

class CFontBuilder final
{
public:
	CFontBuilder( const CFileSystem &p_filesystem ) :
		m_filesystem { p_filesystem }
	{}
	
	const std::shared_ptr<const CFont> FromFile( const fs::path &path, const u16 size, const CGlyphRange &glyphRange ) const;

private:
	const std::shared_ptr<const CFont> FromTtfFile( const fs::path &path, const u16 size, const CGlyphRange &glyphRange ) const;
	const std::shared_ptr<const CFont> FromDummy() const;
	
	const CFileSystem &m_filesystem;
};

