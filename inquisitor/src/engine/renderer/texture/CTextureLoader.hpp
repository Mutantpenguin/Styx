#ifndef CTEXTURELOADER_HPP
#define CTEXTURELOADER_HPP

#include <memory>

#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"

class CTextureLoader final
{
	friend class CTextureManager;

private:
	std::shared_ptr< CTexture > Create2DTextureFromFile( const CFileSystem &filesystem, const std::string &path, const GLint iMaxTextureSize, const std::uint8_t iPicMip );
	std::shared_ptr< CTexture > CreateCubeTextureFromFile( const CFileSystem &filesystem, const std::string &path, const GLint iMaxCubeMapTextureSize, const std::uint8_t iPicMip );
	std::shared_ptr< CTexture > Create2DArrayTextureFromFile( const CFileSystem &filesystem, const std::string &path, const GLint iMaxTextureSize, const std::uint8_t iPicMip );

	std::shared_ptr< CTexture > CreateDummyTexture( void );
};

#endif // CTEXTURELOADER_HPP
