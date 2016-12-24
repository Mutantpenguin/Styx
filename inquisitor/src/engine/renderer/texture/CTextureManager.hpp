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
	CTextureManager( const CSettings &psettings, const CFileSystem &p_filesystem, const CRendererCapabilities &rendererCapabilities );
	virtual ~CTextureManager( void );

	void Update( void );

	std::shared_ptr< CTexture > LoadTexture( const std::string &path );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	const CFileSystem &m_filesystem;

	CTextureLoader m_textureLoader;

	const std::shared_ptr< CTexture > m_dummyTexture;

	std::unordered_map< std::string, std::shared_ptr< CTexture > > m_textures;
};

#endif // CTEXTUREMANAGER_HPP
