#pragma once

#include <memory>

#include "src/system/CFileSystem.hpp"

#include "src/renderer/shader/CShaderProgram.hpp"

class CShaderProgramLoader final
{
public:
	CShaderProgramLoader( const CFileSystem &p_filesystem );
	~CShaderProgramLoader();

	void FromFile( const std::shared_ptr<CShaderProgram> &shaderProgram, const CShaderProgram::ResourceIdType &id ) const;

private:
	const CFileSystem &m_filesystem;
};