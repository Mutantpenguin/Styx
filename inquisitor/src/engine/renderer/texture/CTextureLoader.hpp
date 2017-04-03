#ifndef CTEXTURELOADER_HPP
#define CTEXTURELOADER_HPP

#include <memory>

#include "src/engine/system/CSettings.hpp"
#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"

class CTextureLoader final
{
	friend class CTextureManager;

private:
	CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );

	std::shared_ptr< CTexture > FromFile( const std::string &path ) const;
	std::shared_ptr< CTexture > FromImage( const std::shared_ptr< const CImage > &image ) const;

	std::shared_ptr< CTexture > FromImageFile( const std::string &path ) const;
	std::shared_ptr< CTexture > FromCubeFile( const std::string &path ) const;
	std::shared_ptr< CTexture > From2DArrayFile( const std::string &path ) const;

	std::shared_ptr< CTexture > FromDummy( void ) const;

private:
	const CFileSystem &m_filesystem;

	const std::uint8_t m_iPicMip { 0 };

	GLint m_iMaxTextureSize;
	GLint m_iMaxCubeMapTextureSize;

	const GLint m_internalTextureFormat2D;
	const GLint m_internalTextureFormatCube;
	const GLint m_internalTextureFormat2DArray;

	const std::uint8_t MAX_TEXTURE_PICMIP { 4 };
};

#endif // CTEXTURELOADER_HPP
