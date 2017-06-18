#ifndef CMATERIALMANAGER_HPP
#define CMATERIALMANAGER_HPP

#include <cstdint>
#include <unordered_map>

#include "src/engine/renderer/material/CMaterial.hpp"

#include "src/engine/renderer/shader/CShaderManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

#include "src/engine/renderer/material/CMaterialLoader.hpp"

class CMaterialManager final
{
friend class CRenderer;

public:
	[[nodiscard]] const std::shared_ptr< const CMaterial > LoadMaterial( const std::string &path );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	CMaterialManager( const CFileSystem &filesystem );
	virtual ~CMaterialManager( void );

	void Update( void );

	void ReloadMaterials( void );

	struct sMaterialFile
	{
		std::shared_ptr< CMaterial >	material;
		std::int64_t					mtime;
	};

	CShaderManager &ShaderManager( void );

	const CFileSystem &m_filesystem;

	CShaderManager	m_shaderManager;

	const CMaterialLoader m_materialLoader;

	std::unordered_map< std::string, sMaterialFile > m_materialFiles;
};

#endif // CMATERIALMANAGER_HPP
