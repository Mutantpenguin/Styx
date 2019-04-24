#pragma once

#include "src/core/Types.hpp"

#include "CMaterial.hpp"

#include "src/system/CFileSystem.hpp"
#include "src/resource/CResourceCacheManager.hpp"

#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CMaterialLoader final
{
public:
	CMaterialLoader( const CFileSystem &filesystem, CResourceCacheManager &resourceCacheManager, const CShaderProgramCompiler &shaderProgramCompiler );
	~CMaterialLoader();

	void FromFile( const std::shared_ptr< CMaterial > &material, const fs::path &path ) const;

private:
	bool FromMatFile( const std::shared_ptr< CMaterial > &material, const fs::path &path ) const;

	void FromMatDummy( const std::shared_ptr< CMaterial > &material ) const;

	const CFileSystem &m_filesystem;

	CResourceCacheManager &m_resourceCacheManager;

	const CShaderProgramCompiler &m_shaderProgramCompiler;

	static u16 m_dummyCounter;
};
