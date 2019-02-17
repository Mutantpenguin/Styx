#pragma once

#include "src/helper/Types.hpp"

#include "CMaterial.hpp"

#include "src/renderer/shader/CShaderManager.hpp"
#include "src/renderer/texture/CTextureCache.hpp"
#include "src/renderer/sampler/CSamplerManager.hpp"

class CMaterialLoader final
{
public:
	CMaterialLoader( const CFileSystem &filesystem, CShaderManager &shaderManager );
	~CMaterialLoader();

	void FromFile( const std::shared_ptr< CMaterial > &material, const std::string &path ) const;

private:
	bool FromMatFile( const std::shared_ptr< CMaterial > &material, const std::string &path ) const;

	void FromDummy( const std::shared_ptr< CMaterial > &material ) const;

	const CFileSystem &m_filesystem;

	CShaderManager &m_shaderManager;

	static u16 m_dummyCounter;
};
