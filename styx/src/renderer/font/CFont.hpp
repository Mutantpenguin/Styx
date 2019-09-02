#pragma once

#include <memory>
#include <unordered_map>

#include "external/stb/stb_truetype.h"

#include "src/core/Types.hpp"

#include "src/helper/CSize.hpp"

#include "src/renderer/texture/CTexture.hpp"

class CFont final
{
	friend class CFontBuilder;
public:
	CFont();
	~CFont();
	
	CSize AtlasSize;
	
	u16 Size;
	
	std::shared_ptr<CTexture> Texture;
	
	bool HasCodepoint( const u32 codepoint ) const;
	
	u32 IndexFromCodepoint( const u32 codepoint ) const;

private:
	std::unordered_map<u32, u32> m_codepoints;
	
	std::unique_ptr<stbtt_packedchar[]> m_packedChars;
};
