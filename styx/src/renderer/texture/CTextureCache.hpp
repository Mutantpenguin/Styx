#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/system/CSettings.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"
#include "src/renderer/texture/CTexture.hpp"

class CTextureCache final : public CResourceCache< CTexture >
{
public:
	CTextureCache( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
		CResourceCache( "texture", p_filesystem ),
		m_textureLoader( p_settings, p_filesystem, openGlAdapter )
	{}

private:
	void Load( const std::shared_ptr< CTexture > &resource, const CTexture::ResourceIdType &id ) const override
	{
		m_textureLoader.FromFile( resource, id );
	}

	i64 GetMtime( const CTexture::ResourceIdType &id ) const override
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

	const CTextureLoader m_textureLoader;
};
