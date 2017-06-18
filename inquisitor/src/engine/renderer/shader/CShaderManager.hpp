#ifndef CSHADERMANAGER_HPP
#define CSHADERMANAGER_HPP

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
	CShaderManager( const CFileSystem &p_filesystem );
	~CShaderManager();

	[[nodiscard]] std::shared_ptr< CShaderProgram > LoadProgram( const std::string &pathVertexShader, const std::string &pathFragmentShader );

	[[nodiscard]] std::shared_ptr< CShaderProgram > CreateProgramFromStrings( const std::string &vertexShaderString, const std::string &fragmentShaderString ) const;

	[[nodiscard]] std::shared_ptr< CShaderProgram > GetDummyShader( void ) const;

	constexpr static const GLint requiredCombinedTextureImageUnits { 16 };

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	bool CreateDummyProgram( void );

	GLuint CreateProgram( const GLuint vertexShader, const GLuint fragmentShader ) const;

	[[nodiscard]] GLuint LoadVertexShader( const std::string &path );
	[[nodiscard]] GLuint LoadFragmentShader( const std::string &path );
	[[nodiscard]] GLuint LoadShader( const GLenum type, const std::string &path ) const;

	GLuint CreateShader( const GLenum type, const std::string &body ) const;

	bool InterfaceSetup( std::shared_ptr< CShaderProgram > &shaderProgram ) const;

	void RegisterUniformBuffer( const std::shared_ptr< const CUniformBuffer > &ubo );

	const CFileSystem &m_filesystem;

	std::unordered_map< std::string, std::shared_ptr< CShaderProgram > > m_programs;

	std::unordered_map< std::string, GLuint > m_vertexShaders;
	std::unordered_map< std::string, GLuint > m_fragmentShaders;

	std::unordered_set< std::shared_ptr< const CUniformBuffer > > m_registeredUniformBuffers;

	static const std::string srcAdditionShaderVersion;
	static const std::string srcAdditionVsShaderExtensions;
	static const std::string srcAdditionFsShaderExtensions;

	static const std::map< const CVAO::EAttributeLocation, const SShaderInterface > allowedAttributes;

	static const std::unordered_map< const EEngineUniform, const SShaderInterface > engineUniforms;

	std::shared_ptr< CShaderProgram > m_dummyProgram;
};

#endif // CSHADERMANAGER_HPP
