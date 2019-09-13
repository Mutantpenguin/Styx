#pragma once

#include <memory>

#include "src/system/CFileSystem.hpp"

#include "src/renderer/font/CFont.hpp"

#include "src/renderer/font/CGlyphRange.hpp"

class CFontBuilder final
{
public:
	CFontBuilder( const CFileSystem &p_filesystem ) :
		m_filesystem { p_filesystem }
	{}
	
	const std::shared_ptr<const CFont> FromFile( const std::string &name, const fs::path &pathRegular, const fs::path &pathBold, const u16 size, const CGlyphRange &glyphRange ) const;
	const std::shared_ptr<const CFont> FromFile( const std::string &name, const fs::path &pathRegular, const u16 size, const CGlyphRange &glyphRange ) const;

private:
	const std::shared_ptr<const CFont> FromDummy( const u16 size ) const;

	bool PackFont( stbtt_pack_context &context, const f16 size, std::vector<i32> &glyphs, CFileSystem::FileBuffer &fileBuffer, CFont::CodepointMap &codepointMap ) const;
	
	const CFileSystem &m_filesystem;
};

