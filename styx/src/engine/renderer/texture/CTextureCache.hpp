#pragma once

#include <unordered_map>

#include "src/engine/resource/CResourceCache.hpp"

#include "src/engine/system/CSettings.hpp"

#include "src/engine/renderer/texture/CTextureLoader.hpp"
#include "src/engine/renderer/texture/CTexture.hpp"

class CTextureCache final : public CResourceCache< CTexture >
{
public:
	CTextureCache( const CSettings &psettings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );

private:
	void LoadFromFile( const std::shared_ptr< CTexture > &resource, const std::string &path ) override;

	const CTextureLoader m_textureLoader;
};
