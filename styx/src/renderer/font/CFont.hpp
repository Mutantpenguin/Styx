#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "external/stb/stb_truetype.h"

#include "src/core/Types.hpp"

#include "src/helper/CSize.hpp"

#include "src/renderer/texture/CTexture.hpp"

class CFont final
{
public:
	CFont();
	~CFont();
	
	std::string Name;
	
	CSize AtlasSize;
	
	u16 Size;
	
	std::shared_ptr<CTexture> Texture;
	
	bool HasCodepoint( const u32 codepoint ) const;
	
	u32 IndexFromCodepoint( const u32 codepoint ) const;

	std::unordered_map<u32, u32> Codepoints;
	
	std::unique_ptr<stbtt_packedchar[]> PackedChars;
};
