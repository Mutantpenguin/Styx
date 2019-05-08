#pragma once

#include <memory>

#include "src/core/Types.hpp"

#include "src/helper/image/CImage.hpp"

#include "src/system/CSettings.hpp"
#include "src/system/CFileSystem.hpp"

#include "src/renderer/texture/CTexture.hpp"

#include "src/renderer/COpenGlAdapter.hpp"

#include "src/renderer/texture/CCubemapData.hpp"
#include "src/renderer/texture/C2DArrayData.hpp"

class CTextureLoader final
{
public:
	CTextureLoader( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );
	~CTextureLoader();

	void FromFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;

private:
	void FromImage( const std::shared_ptr<CTexture> &texture, const std::shared_ptr<const CImage> &image ) const;

	bool FromImageFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;
	bool FromCubeFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;
	bool From2DArrayFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;

	bool FromCubemapData( const std::shared_ptr<CTexture> &texture, const CCubemapData &cubemapData ) const;
	bool From2DArrayData( const std::shared_ptr<CTexture> &texture, const C2DArrayData &arrayData ) const;

	void FromImageDummy( const std::shared_ptr<CTexture> &texture ) const;
	void FromCubeDummy( const std::shared_ptr<CTexture> &texture ) const;
	void From2DArrayDummy( const std::shared_ptr<CTexture> &texture ) const;

	const CFileSystem &m_filesystem;

	const u8 m_iPicMip { 0 };

	const COpenGlAdapter &m_openGlAdapter;

	const u8 MAX_TEXTURE_PICMIP { 4 };

	const std::shared_ptr<const CImage> m_dummyImage;
};
