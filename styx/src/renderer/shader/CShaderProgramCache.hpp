#pragma once

#include "src/resource/CResourceCache.hpp"
#include "src/resource/CResourceCacheManager.hpp"

#include "src/renderer/shader/CShaderProgram.hpp"
#include "src/renderer/shader/CShaderProgramCompiler.hpp"
#include "src/renderer/shader/CShaderCache.hpp"

class CShaderProgramCache final : public CResourceCache< CShaderProgram >
{
public:
	CShaderProgramCache( const CFileSystem &p_filesystem, CResourceCacheManager &resourceCacheManager, CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler ) :
		CResourceCache( "shaderprogram", p_filesystem ),
		m_resourceCacheManager { resourceCacheManager },
		m_shaderCompiler { shaderCompiler },
		m_shaderProgramCompiler { shaderProgramCompiler }
	{}

private:
	void Load( const std::shared_ptr< CShaderProgram > &resource, const CShaderProgram::ResourceIdType &id ) const override;

	i64 GetMtime( const CShaderProgram::ResourceIdType &id ) const override
	{
		if( id.geometryShader.empty() )
		{
			return( std::max( { m_filesystem.GetLastModTime( id.vertexShader ), m_filesystem.GetLastModTime( id.fragmentShader ) } ) );
		}
		else
		{
			return( std::max( { m_filesystem.GetLastModTime( id.vertexShader ), m_filesystem.GetLastModTime( id.geometryShader ), m_filesystem.GetLastModTime( id.fragmentShader ) } ) );
		}
	}

private:
	CResourceCacheManager &m_resourceCacheManager;
	
	CShaderCompiler			&m_shaderCompiler;
	CShaderProgramCompiler	&m_shaderProgramCompiler;
};