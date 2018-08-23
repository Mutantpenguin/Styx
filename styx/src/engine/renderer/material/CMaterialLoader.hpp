#ifndef CMATERIALLOADER_HPP
#define CMATERIALLOADER_HPP

#include <cstdint>

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

	static std::uint16_t m_dummyCounter;
};

#endif // CMATERIALLOADER_HPP
