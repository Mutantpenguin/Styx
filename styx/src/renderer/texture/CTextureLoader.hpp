#pragma once

#include <memory>

#include "src/core/Types.hpp"

#include "src/helper/image/CImage.hpp"

#include "src/system/CFileSystem.hpp"

#include "src/renderer/texture/CTexture.hpp"

#include "src/renderer/COpenGlAdapter.hpp"

#include "src/renderer/texture/CCubemapData.hpp"
#include "src/renderer/texture/C2DArrayData.hpp"

class CTextureLoader final
{
public:
	CTextureLoader( const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );
	~CTextureLoader();

	void FromFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;
	
	static void FromImage( const std::shared_ptr<CTexture> &texture, const std::shared_ptr<const CImage> &image );

private:
	bool FromImageFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;
	bool FromCubeFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;
	bool From2DArrayFile( const std::shared_ptr<CTexture> &texture, const fs::path &path ) const;

	bool FromCubemapData( const std::shared_ptr<CTexture> &texture, const CCubemapData &cubemapData ) const;
	bool From2DArrayData( const std::shared_ptr<CTexture> &texture, const C2DArrayData &arrayData ) const;

	void FromImageDummy( const std::shared_ptr<CTexture> &texture ) const;
	void FromCubeDummy( const std::shared_ptr<CTexture> &texture ) const;
	void From2DArrayDummy( const std::shared_ptr<CTexture> &texture ) const;
	
	static GLenum PreferredInternalFormatFromImage( const GLenum target, const std::shared_ptr<const CImage> &image );
	static GLenum FormatFromImage( const std::shared_ptr<const CImage> &image );

	const CFileSystem &m_filesystem;

	const COpenGlAdapter &m_openGlAdapter;

	const std::shared_ptr<const CImage> m_dummyImage;
};
