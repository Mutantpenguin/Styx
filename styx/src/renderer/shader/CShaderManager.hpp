#pragma once

#include <unordered_map>
#include <map>

#include "src/renderer/GL.h"

#include "src/system/CFileSystem.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgram.hpp"

#include "src/resource/CResourceCacheManager.hpp"

class CShaderManager
{
	friend class CRenderer;

public:
	explicit CShaderManager( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler, CResourceCacheManager &resourceCacheManager );
	~CShaderManager();

	[[nodiscard]] const std::shared_ptr<const CShaderProgram> LoadProgram( const CShaderProgram::ResourceIdType &paths );

	[[nodiscard]] const std::shared_ptr<const CShaderProgram> CreateProgramFromShaders( const std::shared_ptr<const CShader> &vertexShader, const std::shared_ptr<const CShader> &fragmentShader ) const;

	[[nodiscard]] const std::shared_ptr<const CShaderProgram> GetDummyShader() const;

	constexpr static const GLint requiredCombinedTextureImageUnits { 16 };

	class Exception: public std::exception
	{
	public:
		explicit Exception() {}

		virtual ~Exception() throw() {}
	};

private:
	[[nodiscard]] bool CreateDummyProgram();

	[[nodiscard]] GLuint CreateProgram( const std::shared_ptr<const CShader> &vertexShader, const std::shared_ptr<const CShader> &fragmentShader ) const;

	[[nodiscard]] bool InterfaceSetup( const std::shared_ptr<CShaderProgram> &shaderProgram ) const;

	const CFileSystem		&m_filesystem;
	const CShaderCompiler	&m_shaderCompiler;
	
	CResourceCacheManager	&m_resourceCacheManager;

	std::unordered_map< std::string, std::shared_ptr<CShaderProgram> > m_programs;

	std::shared_ptr<CShaderProgram> m_dummyProgram;

	
};
