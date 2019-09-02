#pragma once

#include <memory>
#include <vector>

#include "src/core/Types.hpp"

#include "src/helper/CSize.hpp"

#include "src/renderer/texture/CTexture.hpp"

class CFont final
{
public:
	CFont();
	~CFont();
	
	CSize AtlasSize;
	
	u16 Size;
	
	std::shared_ptr<CTexture> Texture;
	
	bool ContainsCodepoint( const u32 codepoint ) const;

private:
	std::vector<u32> m_codepoints;
};
