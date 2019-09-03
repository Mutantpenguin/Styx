#pragma once

#include "src/core/Types.hpp"

#include "CMaterial.hpp"

#include "src/system/CFileSystem.hpp"
#include "src/resource/CResources.hpp"

#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CMaterialLoader final
{
public:
	CMaterialLoader( const CFileSystem &filesystem, CResources &resources, const std::shared_ptr<const CShaderProgram> &dummyShaderProgram );
	~CMaterialLoader();

	void FromFile( const std::shared_ptr<CMaterial> &material, const fs::path &path ) const;

private:
	bool FromMatFile( const std::shared_ptr<CMaterial> &material, const fs::path &path ) const;

	void FromDummy( const std::shared_ptr<CMaterial> &material ) const;

	const CFileSystem &m_filesystem;

	CResources &m_resources;

	const std::shared_ptr<const CShaderProgram> m_dummyShaderProgram;

	static u16 m_dummyCounter;
};
