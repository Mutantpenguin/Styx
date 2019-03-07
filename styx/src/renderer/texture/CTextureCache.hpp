#pragma once

#include <unordered_map>

#include "src/resource/CResourceCache.hpp"

#include "src/system/CSettings.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"
#include "src/renderer/texture/CTexture.hpp"

class CTextureCache final : public CResourceCache< CTexture >
{
public:
	CTextureCache( const CSettings &psettings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter );

private:
	void Load( const std::shared_ptr< CTexture > &resource, const CTexture::ResourceIdType &id ) override
	{
		m_textureLoader.FromFile( resource, id );
	}

	i64 GetMtime( const CTexture::ResourceIdType &id )
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

	const CTextureLoader m_textureLoader;
};
