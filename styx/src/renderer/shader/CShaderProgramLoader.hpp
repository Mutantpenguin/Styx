#pragma once

#include <memory>

#include "src/system/CFileSystem.hpp"

#include "src/resource/CResources.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"

#include "src/renderer/shader/CShaderProgram.hpp"
#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CShaderProgramLoader final
{
public:
	CShaderProgramLoader( const CFileSystem &p_filesystem, CResources &resources, CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler );
	~CShaderProgramLoader();
	
	void FromFile( const std::shared_ptr<CShaderProgram> &shaderProgram, const fs::path &path ) const;

private:
	bool FromShpFile( const std::shared_ptr<CShaderProgram> &shaderProgram, const fs::path &path ) const;
	void FromDummy( const std::shared_ptr<CShaderProgram> &shaderProgram ) const;

	const CFileSystem &m_filesystem;

	CResources &m_resources;
	
	CShaderCompiler			&m_shaderCompiler;
	CShaderProgramCompiler	&m_shaderProgramCompiler;
};