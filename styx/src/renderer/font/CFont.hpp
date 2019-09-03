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
	std::string Name;
	
	CSize AtlasSize;
	
	u16 Size;
	
	std::shared_ptr<CTexture> Texture;
	
	bool HasCodepoint( const u32 codepoint ) const;
	
	const stbtt_packedchar * PackedCharFromCodepoint( const u32 codepoint ) const;

	std::unordered_map<u32, stbtt_packedchar> Codepoints;
};
