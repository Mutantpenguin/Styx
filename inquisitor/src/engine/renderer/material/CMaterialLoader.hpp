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
	static std::shared_ptr< CMaterial > CreateMaterial( CTextureManager &textureManager, CShaderManager &shaderManager, const CSamplerManager &samplerManager, const std::string &identifier, const std::string &definition );

	static std::shared_ptr< CMaterial > CreateDummyMaterial( CShaderManager &shaderManager );
};

#endif // CMATERIALLOADER_HPP
