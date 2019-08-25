#pragma once

#include <memory>
#include <unordered_map>

#include "src/core/Types.hpp"

#include "src/renderer/texture/CTexture.hpp"

class CFont final
{
public:
	CFont() {}
	~CFont();
	
	void Reset();

private:
	std::unordered_map<i8, std::shared_ptr<CTexture>> m_textures;
};
