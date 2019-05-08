#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/material/CMaterial.hpp"

#include "src/renderer/material/CMaterialLoader.hpp"

#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CMaterialCache final : public CResourceCache< CMaterial >
{
public:
	CMaterialCache( const CFileSystem &filesystem, CResources &resources, const CShaderProgramCompiler &shaderProgramCompiler ) :
		CResourceCache( "material", filesystem ),
		m_materialLoader( filesystem, resources, shaderProgramCompiler )
	{}

private:
	void Load( const std::shared_ptr< CMaterial > &resource, const CMaterial::ResourceIdType &id ) const override
	{
		m_materialLoader.FromFile( resource, id );
	}

	i64 GetMtime( const CMaterial::ResourceIdType &id ) const override
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

	const CMaterialLoader m_materialLoader;
};
