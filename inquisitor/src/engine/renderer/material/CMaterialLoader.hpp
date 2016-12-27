#ifndef CMATERIALLOADER_HPP
#define CMATERIALLOADER_HPP

#include "CMaterial.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"
#include "src/engine/renderer/texture/CTextureManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

class CMaterialLoader final
{
	friend class CMaterialManager;

private:
	CMaterialLoader( const CFileSystem &filesystem, CTextureManager &textureManager, CShaderManager &shaderManager, const CSamplerManager &samplerManager );

	std::shared_ptr< CMaterial > CreateMaterialFromFile( const std::string &path ) const;

	std::shared_ptr< CMaterial > CreateMaterialFromMatFile( const std::string &path ) const;

	std::shared_ptr< CMaterial > CreateDummyMaterial( void ) const;

private:
	const CFileSystem &m_filesystem;

	CTextureManager &m_textureManager;

	CShaderManager &m_shaderManager;

	const CSamplerManager &m_samplerManager;
};

#endif // CMATERIALLOADER_HPP
