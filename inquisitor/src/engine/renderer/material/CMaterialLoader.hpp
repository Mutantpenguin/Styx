#ifndef CMATERIALLOADER_HPP
#define CMATERIALLOADER_HPP

#include <cstdint>

#include "CMaterial.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"
#include "src/engine/renderer/texture/CTextureManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

class CMaterialLoader final
{
public:
	CMaterialLoader( const CFileSystem &filesystem, CTextureManager &textureManager, CShaderManager &shaderManager, const CSamplerManager &samplerManager );
	~CMaterialLoader( void );

	void FromFile( const std::string &path, std::shared_ptr< CMaterial > mat ) const;

private:
	bool FromMatFile( const std::string &path, std::shared_ptr< CMaterial > mat ) const;

	void FromDummy( std::shared_ptr< CMaterial > mat ) const;

	const CFileSystem &m_filesystem;

	CTextureManager &m_textureManager;

	CShaderManager &m_shaderManager;

	const CSamplerManager &m_samplerManager;

	static std::uint16_t m_dummyCounter;
};

#endif // CMATERIALLOADER_HPP
