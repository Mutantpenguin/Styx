#pragma once

#include "src/resource/CResourceCache.hpp"

#include "src/renderer/shader/CShaderProgram.hpp"

class CShaderProgramCache final : public CResourceCache< CShaderProgram >
{
public:
	CShaderProgramCache( const CFileSystem &p_filesystem );

private:
	void Load( const std::shared_ptr< CShaderProgram > &resource, const CShaderProgram::ResourceIdType &id )  const override
	{
		// TODO m_textureLoader.FromFile(resource, id);
	}

	i64 GetMtime( const CShaderProgram::ResourceIdType &id ) const override
	{
		return( std::max( m_filesystem.GetLastModTime( id.vertexShader ), m_filesystem.GetLastModTime( id.fragmentShader ) ) );
	}

	// TODO const CShaderProgramLoader m_shaderProgramLoader;
};