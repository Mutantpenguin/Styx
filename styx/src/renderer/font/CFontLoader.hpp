#pragma once

#include <memory>

#include "src/system/CFileSystem.hpp"

#include "src/renderer/font/CFont.hpp"

class CFontLoader final
{
public:
	CFontLoader( const CFileSystem &p_filesystem );
	~CFontLoader();
	
	void FromFile( const std::shared_ptr<CFont> &font, const fs::path &path ) const;

private:
	bool FromTtfFile( const std::shared_ptr<CFont> &font, const fs::path &path ) const;
	void FromDummy( const std::shared_ptr<CFont> &font ) const;
	
	const CFileSystem &m_filesystem;
};

