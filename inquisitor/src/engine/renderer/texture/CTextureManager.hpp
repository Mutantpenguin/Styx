#ifndef CTEXTUREMANAGER_HPP
#define CTEXTUREMANAGER_HPP

#include <unordered_map>

#include "src/engine/system/CSettings.hpp"

#include "src/engine/renderer/texture/CTextureLoader.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"
#include "src/engine/renderer/CRendererCapabilities.hpp"

class CTextureManager final
{
public:
	CTextureManager( const CSettings &psettings, const CFileSystem &p_filesystem );
	virtual ~CTextureManager( void );

	bool Init( const CRendererCapabilities &rendererCapabilities );

	void Update( void );

	std::shared_ptr< CTexture > LoadTexture( const std::string &path );

private:
	const CFileSystem &m_filesystem;

	CTextureLoader m_textureLoader;

	std::shared_ptr< CTexture > m_dummyTexture;

	GLint	m_iMaxTextureSize;
	GLint	m_iMaxCubeMapTextureSize;

	const std::uint8_t	m_iPicMip { 0 };

	const std::uint8_t MAX_PICMIP { 4 };

	std::unordered_map< std::string, std::shared_ptr< CTexture > > m_textures;
};

#endif // CTEXTUREMANAGER_HPP
