#pragma once

#include <cstdint>
#include <unordered_map>

#include "src/engine/resource/CResourceCache.hpp"

#include "src/engine/renderer/material/CMaterial.hpp"

#include "src/engine/renderer/material/CMaterialLoader.hpp"

class CMaterialCache final  : public CResourceCache< CMaterial >
{
public:
	CMaterialCache( const CFileSystem &filesystem, CShaderManager	&shaderManager );

private:
	void LoadFromFile( const std::shared_ptr< CMaterial > &resource, const std::string &path ) override;

	const CMaterialLoader m_materialLoader;
};
