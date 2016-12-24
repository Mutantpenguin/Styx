#ifndef CTEXTURELOADER_HPP
#define CTEXTURELOADER_HPP

#include <memory>

#include "src/engine/system/CSettings.hpp"
#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/renderer/CRendererCapabilities.hpp"

class CTextureLoader final
{
	friend class CTextureManager;

private:
	CTextureLoader( const CSettings &p_settings, const CRendererCapabilities &rendererCapabilities );

	std::shared_ptr< CTexture > Create2DTextureFromFile( const CFileSystem &filesystem, const std::string &path );
	std::shared_ptr< CTexture > CreateCubeTextureFromFile( const CFileSystem &filesystem, const std::string &path );
	std::shared_ptr< CTexture > Create2DArrayTextureFromFile( const CFileSystem &filesystem, const std::string &path );

	std::shared_ptr< CTexture > CreateDummyTexture( void );

	GLint m_iMaxTextureSize;
	GLint m_iMaxCubeMapTextureSize;

	const std::uint8_t m_iPicMip { 0 };

	const std::uint8_t MAX_PICMIP { 4 };
};

#endif // CTEXTURELOADER_HPP
