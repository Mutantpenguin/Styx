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

	[[nodiscard]] const std::shared_ptr< const CTexture > LoadTexture( const std::string &path );

	void ReloadTextures( void );

private:
	struct sTextureFile
	{
		std::shared_ptr< CTexture >	texture;
		std::int64_t				mtime;
	};

	const CFileSystem &m_filesystem;

	const CTextureLoader m_textureLoader;

	std::unordered_map< std::string, sTextureFile > m_textureFiles;
};

#endif // CTEXTUREMANAGER_HPP
