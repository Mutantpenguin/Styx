#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/font/CFontLoader.hpp"
#include "src/renderer/font/CFont.hpp"

class CFontCache final : public CResourceCache<CFont>
{
public:
	CFontCache( const CFileSystem &p_filesystem ) :
		CResourceCache( "font", p_filesystem ),
		m_fontLoader( p_filesystem )
	{}

private:
	void Load( const std::shared_ptr<CFont> &resource, const std::string &id ) const override
	{
		m_fontLoader.FromFile( resource, id );
	}

	const CFontLoader m_fontLoader;
};
