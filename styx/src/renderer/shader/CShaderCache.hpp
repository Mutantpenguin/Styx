#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/shader/CShaderLoader.hpp"
#include "src/renderer/shader/CShader.hpp"

class CShaderCache final : public CResourceCache< CShader >
{
public:
	CShaderCache( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler ) :
		CResourceCache( "texture", p_filesystem ),
		m_shaderLoader( p_filesystem, shaderCompiler )
	{}

private:
	void Load( const std::shared_ptr< CShader > &resource, const CShader::ResourceIdType &id ) const override
	{
		m_shaderLoader.FromFile( resource, id );
	}

	i64 GetMtime( const CShader::ResourceIdType &id ) const override
	{
		return( m_filesystem.GetLastModTime( id ) );
	}

	const CShaderLoader m_shaderLoader;
};
