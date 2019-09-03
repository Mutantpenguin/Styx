#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/material/CMaterial.hpp"

#include "src/renderer/material/CMaterialLoader.hpp"

#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CMaterialCache final : public CResourceCache<CMaterial>
{
public:
	CMaterialCache( const CFileSystem &filesystem, CResources &resources, const std::shared_ptr<const CShaderProgram> &dummyShaderProgram ) :
		CResourceCache( "material", filesystem ),
		m_materialLoader( filesystem, resources, dummyShaderProgram )
	{}

private:
	void Load( const std::shared_ptr<CMaterial> &resource, const std::string &id ) const override
	{
		m_materialLoader.FromFile( resource, id );
	}

	const CMaterialLoader m_materialLoader;
};
