#pragma once

#include <memory>

#include "src/engine/helper/Types.hpp"

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

	void FromFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const;

private:
	void FromImage( const std::shared_ptr< CTexture > &texture, const std::shared_ptr< const CImage > &image ) const;

	bool FromImageFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const;
	bool FromCubeFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const;
	bool From2DArrayFile( const std::shared_ptr< CTexture > &texture, const std::string &path ) const;

	bool FromCubemapData( const std::shared_ptr< CTexture > &texture, const CCubemapData &cubemapData ) const;
	bool From2DArrayData( const std::shared_ptr< CTexture > &texture, const C2DArrayData &arrayData ) const;

	void FromDummy( const std::shared_ptr< CTexture > &texture ) const;

	const CFileSystem &m_filesystem;

	const u8 m_iPicMip { 0 };

	const COpenGlAdapter &m_openGlAdapter;

	const u8 MAX_TEXTURE_PICMIP { 4 };

	const std::shared_ptr< const CImage > m_dummyImage;
};
