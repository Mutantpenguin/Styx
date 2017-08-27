#ifndef CTEXTURELOADER_HPP
#define CTEXTURELOADER_HPP

#include <memory>

#include "src/engine/helper/image/CImage.hpp"

#include "src/engine/system/CSettings.hpp"
#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"

#include "src/engine/renderer/texture/CCubemapData.hpp"
#include "src/engine/renderer/texture/C2DArrayData.hpp"

class CTextureLoader final
{
public:
	CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );
	~CTextureLoader( void );

	void FromFile( const std::string &path, const std::shared_ptr< CTexture > &texture ) const;

private:
	void FromImage( const std::shared_ptr< const CImage > &image, const std::shared_ptr< CTexture > &texture ) const;

	bool FromImageFile( const std::string &path, const std::shared_ptr< CTexture > &texture ) const;
	bool FromCubeFile( const std::string &path, const std::shared_ptr< CTexture > &texture ) const;
	bool From2DArrayFile( const std::string &path, const std::shared_ptr< CTexture > &texture ) const;

	bool FromCubemapData( const CCubemapData &cubemapData, const std::shared_ptr< CTexture > &texture ) const;
	bool From2DArrayData( const C2DArrayData &arrayData, const std::shared_ptr< CTexture > &texture ) const;

	void FromDummy( const std::shared_ptr< CTexture > &texture ) const;

	const CFileSystem &m_filesystem;

	const std::uint8_t m_iPicMip { 0 };

	const COpenGlAdapter &m_openGlAdapter;

	const std::uint8_t MAX_TEXTURE_PICMIP { 4 };

	const std::shared_ptr< const CImage > m_dummyImage;
};

#endif // CTEXTURELOADER_HPP
