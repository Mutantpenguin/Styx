#pragma once

#include <memory>
#include <string>
#include <optional>
#include <unordered_map>

#include "external/stb/stb_truetype.h"

#include "src/core/Types.hpp"

#include "src/helper/CSize.hpp"

#include "src/renderer/texture/CTexture.hpp"

#include "EFontStyle.hpp"

class CFont final
{
public:	
	CFont( const std::string &name, const u16 size, const CSize &atlasSize );
	
	const std::string Name;
	
	const u16 Size;

	const CSize AtlasSize;
	
	std::shared_ptr<CTexture> Texture = std::make_shared<CTexture>();
	
	bool HasCodepoint( EFontStyle fontStyle, const u32 codepoint ) const;
	
	const stbtt_packedchar * PackedCharFromCodepoint( EFontStyle fontStyle, const u32 codepoint ) const;

	using CodepointMap = std::unordered_map<u32, stbtt_packedchar>;

	CodepointMap CodepointsMedium;
	std::optional<CodepointMap> CodepointsBold;
};
