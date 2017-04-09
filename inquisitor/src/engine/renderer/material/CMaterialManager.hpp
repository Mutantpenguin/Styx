#ifndef CMATERIALMANAGER_HPP
#define CMATERIALMANAGER_HPP

#include <cstdint>
#include <unordered_map>

#include "src/engine/renderer/material/CMaterial.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"
#include "src/engine/renderer/texture/CTextureManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

#include "src/engine/renderer/material/CMaterialLoader.hpp"

class CMaterialManager final
{
friend class CRenderer;

public:
	std::shared_ptr< CMaterial > LoadMaterial( const std::string &path );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

	void ReloadMaterials( void );

private:
	CMaterialManager( const CSettings &settings, const CFileSystem &filesystem, const CSamplerManager &samplerManager, const COpenGlAdapter &openGlAdapter );
	virtual ~CMaterialManager( void );

	void	Update( void );

	struct sMaterialFile
	{
		std::shared_ptr< CMaterial >	material;
		std::int64_t					mtime;
	};

private:
	CShaderManager &ShaderManager( void );

	const CFileSystem &m_filesystem;

	const CSamplerManager &m_samplerManager;

	CShaderManager	m_shaderManager;
	CTextureManager m_textureManager;

	const CMaterialLoader m_materialLoader;

	std::unordered_map< std::string, sMaterialFile > m_materialFiles;
};

#endif // CMATERIALMANAGER_HPP
