#pragma once

#include <unordered_map>

#include "src/resource/CResourceCache.hpp"

#include "src/system/CSettings.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"
#include "src/renderer/texture/CTexture.hpp"

class CTextureCache final : public CResourceCache< CTexture >
{
public:
	CTextureCache( const CSettings &psettings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );

private:
	void LoadFromFile( const std::shared_ptr< CTexture > &resource, const std::string &path ) override;

	const CTextureLoader m_textureLoader;
};
