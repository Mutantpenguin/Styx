#pragma once

#include <memory>

#include "src/system/CFileSystem.hpp"

#include "src/renderer/shader/CShader.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"

class CShaderLoader final
{
public:
	CShaderLoader( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler );
	~CShaderLoader();

	void FromFile( const std::shared_ptr<CShader> &shader, const std::string &path ) const;

private:
	void FromVertexDummy( const std::shared_ptr<CShader> &shader ) const;
	void FromFragmentDummy( const std::shared_ptr<CShader> &shader ) const;

	const CFileSystem &m_filesystem;

	const CShaderCompiler &m_shaderCompiler;
};