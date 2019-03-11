#pragma once

#include <unordered_map>
#include <map>

#include "src/renderer/GL.h"

#include "src/system/CFileSystem.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgram.hpp"

class CShaderManager
{
	friend class CRenderer;

public:
	explicit CShaderManager( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler );
	~CShaderManager();

	[[nodiscard]] const std::shared_ptr< const CShaderProgram > LoadProgram( const std::string &pathVertexShader, const std::string &pathFragmentShader );

	[[nodiscard]] const std::shared_ptr< const CShaderProgram > CreateProgramFromStrings( const std::string &vertexShaderString, const std::string &fragmentShaderString ) const;

	[[nodiscard]] const std::shared_ptr< const CShaderProgram > GetDummyShader() const;

	constexpr static const GLint requiredCombinedTextureImageUnits { 16 };

	class Exception: public std::exception
	{
	public:
		explicit Exception() {}

		virtual ~Exception() throw() {}
	};

private:
	[[nodiscard]] bool CreateDummyProgram();

	[[nodiscard]] GLuint CreateProgram( const GLuint vertexShader, const GLuint fragmentShader ) const;

	[[nodiscard]] const std::shared_ptr<const CShader> LoadShader( const GLenum type, const std::string &path );

	[[nodiscard]] bool InterfaceSetup( const std::shared_ptr< CShaderProgram > &shaderProgram ) const;

	const CFileSystem		&m_filesystem;
	const CShaderCompiler	&m_shaderCompiler;

	std::unordered_map< std::string, std::shared_ptr< CShaderProgram > > m_programs;

	std::unordered_map< std::string, std::shared_ptr<const CShader> > m_shaders;

	std::shared_ptr< CShaderProgram > m_dummyProgram;
};
