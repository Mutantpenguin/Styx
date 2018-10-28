#pragma once

#include "src/engine/helper/Types.hpp"

#include "CMaterial.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"
#include "src/engine/renderer/texture/CTextureCache.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

class CMaterialLoader final
{
public:
	CMaterialLoader( const CFileSystem &filesystem, CShaderManager &shaderManager );
	~CMaterialLoader( void );

	void FromFile( const std::shared_ptr< CMaterial > &material, const std::string &path ) const;

private:
	bool FromMatFile( const std::shared_ptr< CMaterial > &material, const std::string &path ) const;

	void FromDummy( const std::shared_ptr< CMaterial > &material ) const;

	const CFileSystem &m_filesystem;

	CShaderManager &m_shaderManager;

	static u16 m_dummyCounter;
};
