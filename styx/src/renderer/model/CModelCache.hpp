#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/model/CModel.hpp"

#include "src/renderer/model/CModelLoader.hpp"


class CModelCache final : public CResourceCache< CModel >
{
public:
	CModelCache( const CFileSystem &filesystem, CResources &resources ) :
		CResourceCache( "model", filesystem ),
		m_modelLoader( filesystem, resources )
	{}

private:
	void Load( const std::shared_ptr< CModel > &resource, const CModel::ResourceIdType &id ) const override
	{
		m_modelLoader.FromFile( resource, id );
	}

	i64 GetMtime( const CModel::ResourceIdType &id ) const override
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

private:
	const CModelLoader m_modelLoader;
};
