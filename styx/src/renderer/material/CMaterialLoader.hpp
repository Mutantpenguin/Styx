#pragma once

#include "src/helper/Types.hpp"

#include "CMaterial.hpp"

#include "src/system/CFileSystem.hpp"
#include "src/resource/CResourceCacheManager.hpp"


class CMaterialLoader final
{
public:
	CMaterialLoader( const CFileSystem &filesystem, CResourceCacheManager &resourceCacheManager );
	~CMaterialLoader();

	void FromFile( const std::shared_ptr< CMaterial > &material, const std::string &path ) const;

private:
	bool FromMatFile( const std::shared_ptr< CMaterial > &material, const std::string &path ) const;

	void FromMatDummy( const std::shared_ptr< CMaterial > &material ) const;

	const CFileSystem &m_filesystem;

	CResourceCacheManager &m_resourceCacheManager;

	static u16 m_dummyCounter;
};
