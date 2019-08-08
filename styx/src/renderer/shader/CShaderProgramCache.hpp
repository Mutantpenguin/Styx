#pragma once

#include "src/resource/CResourceCache.hpp"
#include "src/resource/CResources.hpp"

#include "src/renderer/shader/CShaderProgramLoader.hpp"

class CShaderProgramCache final : public CResourceCache<CShaderProgram>
{
public:
	CShaderProgramCache( const CFileSystem &p_filesystem, CResources &resources, CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler ) :
		CResourceCache( "shaderprogram", p_filesystem ),
		m_shaderProgramLoader( p_filesystem, resources, shaderCompiler, shaderProgramCompiler )
	{}

private:
	void Load( const std::shared_ptr<CShaderProgram> &resource, const std::string &id ) const override
	{
		m_shaderProgramLoader.FromFile( resource, id );
	}

private:
	CShaderProgramLoader	m_shaderProgramLoader;
};