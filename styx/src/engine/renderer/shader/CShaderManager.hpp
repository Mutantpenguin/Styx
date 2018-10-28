#pragma once

#include <unordered_map>
#include <unordered_set>
#include <map>

#include "src/engine/renderer/GL.h"

#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/CUniformBuffer.hpp"

#include "src/engine/renderer/shader/EEngineUniform.hpp"

#include "src/engine/renderer/shader/CShaderProgram.hpp"

#include "src/engine/renderer/CVAO.hpp"

class CShaderManager
{
	friend class CRenderer;

public:
	explicit CShaderManager( const CFileSystem &p_filesystem );
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

	[[nodiscard]] GLuint LoadVertexShader( const std::string &path );
	[[nodiscard]] GLuint LoadFragmentShader( const std::string &path );
	[[nodiscard]] GLuint LoadShader( const GLenum type, const std::string &path ) const;

	[[nodiscard]] GLuint CreateShader( const GLenum type, const std::string &body ) const;

	[[nodiscard]] bool InterfaceSetup( const std::shared_ptr< CShaderProgram > &shaderProgram ) const;

	void RegisterUniformBuffer( const std::shared_ptr< const CUniformBuffer > &ubo );

	const CFileSystem &m_filesystem;

	std::unordered_map< std::string, std::shared_ptr< CShaderProgram > > m_programs;

	std::unordered_map< std::string, GLuint > m_vertexShaders;
	std::unordered_map< std::string, GLuint > m_fragmentShaders;

	std::unordered_set< std::shared_ptr< const CUniformBuffer > > m_registeredUniformBuffers;

	static const std::string srcAdditionShaderVersion;

	static const std::map< const CVAO::EAttributeLocation, const SShaderInterface > allowedAttributes;

	static const std::unordered_map< EEngineUniform, const SShaderInterface > engineUniforms;

	std::shared_ptr< CShaderProgram > m_dummyProgram;
};
