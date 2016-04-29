#ifndef CMATERIALMANAGER_HPP
#define CMATERIALMANAGER_HPP

#include <unordered_map>

#include "CMaterial.hpp"

#include "../shader/CShaderManager.hpp"
#include "../texture/CTextureManager.hpp"
#include "../sampler/CSamplerManager.hpp"

class CMaterialManager final
{
friend class CRenderer;

public:
	std::shared_ptr< CMaterial > LoadMaterial( const std::string &path );

private:
	CMaterialManager( const CSettings &settings, const CFileSystem &filesystem, const CSamplerManager &samplerManager );
	virtual ~CMaterialManager( void );

	bool	Init( const CRendererCapabilities &rendererCapabilities );

	void	Update( const float delta );

private:
	CShaderManager &ShaderManager( void );

	const CFileSystem &m_filesystem;

	const CSamplerManager &m_samplerManager;

	CShaderManager	m_shaderManager;
	CTextureManager m_textureManager;

	void CreateDummyMaterial( void );
	std::shared_ptr< CMaterial > m_dummyMaterial;

	std::unordered_map< std::string, std::weak_ptr< CMaterial > > m_materials;
};

#endif // CMATERIALMANAGER_HPP
