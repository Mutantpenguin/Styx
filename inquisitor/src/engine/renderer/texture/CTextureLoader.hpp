#ifndef CTEXTURELOADER_HPP
#define CTEXTURELOADER_HPP

#include <memory>

#include "src/engine/helper/image/CImage.hpp"

#include "src/engine/system/CSettings.hpp"
#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"

class CTextureLoader final
{
public:
	CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );

	void FromFile( const std::string &path, std::shared_ptr< CTexture > tex ) const;
	void FromImage( const std::shared_ptr< const CImage > &image, std::shared_ptr< CTexture > tex ) const;

private:
	bool FromImageFile( const std::string &path, std::shared_ptr< CTexture > tex ) const;
	bool FromCubeFile( const std::string &path, std::shared_ptr< CTexture > tex ) const;
	bool From2DArrayFile( const std::string &path, std::shared_ptr< CTexture > tex ) const;

	void FromDummy( std::shared_ptr< CTexture > tex ) const;

	const CFileSystem &m_filesystem;

	const std::uint8_t m_iPicMip { 0 };

	GLint m_iMaxTextureSize;
	GLint m_iMaxCubeMapTextureSize;

	const GLint m_internalTextureFormat2D;
	const GLint m_internalTextureFormatCube;
	const GLint m_internalTextureFormat2DArray;

	const std::uint8_t MAX_TEXTURE_PICMIP { 4 };

	const std::shared_ptr< const CImage > m_dummyImage;
};

#endif // CTEXTURELOADER_HPP
