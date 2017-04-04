#ifndef CTEXTUREMANAGER_HPP
#define CTEXTUREMANAGER_HPP

#include <unordered_map>

#include "src/engine/system/CSettings.hpp"

#include "src/engine/renderer/texture/CTextureLoader.hpp"
#include "src/engine/renderer/texture/CTexture.hpp"

class CTextureManager final
{
public:
	CTextureManager( const CSettings &psettings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );
	virtual ~CTextureManager( void );

	void Update( void );

	std::shared_ptr< CTexture > LoadTexture( const std::string &path );

private:
	const CTextureLoader m_textureLoader;

	std::unordered_map< std::string, std::shared_ptr< CTexture > > m_textures;
};

#endif // CTEXTUREMANAGER_HPP
