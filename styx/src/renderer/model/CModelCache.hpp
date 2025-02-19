#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/model/CModel.hpp"

#include "src/renderer/model/CModelLoader.hpp"


class CModelCache final : public CResourceCache<CModel>
{
public:
	CModelCache( const CFileSystem &filesystem, CResources &resources ) :
		CResourceCache( "model", filesystem ),
		m_modelLoader( filesystem, resources )
	{}

private:
	void Load( const std::shared_ptr<CModel> &resource, const std::string &id ) const override
	{
		m_modelLoader.FromFile( resource, id );
	}

private:
	const CModelLoader m_modelLoader;
};
