#pragma once

#include <cstdint>
#include <unordered_map>

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/material/CMaterial.hpp"

#include "src/renderer/material/CMaterialLoader.hpp"

class CMaterialCache final  : public CResourceCache< CMaterial, std::string >
{
public:
	CMaterialCache( const CFileSystem &filesystem, CShaderManager &shaderManager );

private:
	void Load( const std::shared_ptr< CMaterial > &resource, const std::string &id ) override
	{
		m_materialLoader.FromFile( resource, id );
	}

	const CMaterialLoader m_materialLoader;
};
