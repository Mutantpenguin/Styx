#ifndef CSHADERMANAGER_HPP
#define CSHADERMANAGER_HPP

#include <unordered_map>
#include <unordered_set>
#include <map>

#include "../GL.h"

#include "../../system/CFileSystem.hpp"

#include "../CUniformBuffer.hpp"

#include "EReservedUniformLocations.hpp"

#include "CShaderProgram.hpp"

class CShaderManager
{
	friend class CRenderer;

public:
	CShaderManager( const CFileSystem &p_filesystem );
	~CShaderManager();

	bool Init( void );

	std::shared_ptr< CShaderProgram > LoadProgram( const std::string &pathVertexShader, const std::string &pathFragmentShader );

	std::shared_ptr< CShaderProgram > GetDummyShader( void ) const;

	constexpr static const GLint requiredCombinedTextureImageUnits { 16 };

private:
	bool CreateDummyProgram( void );

	GLuint CreateProgram( const GLuint vertexShader, const GLuint fragmentShader );

	GLuint LoadVertexShader( const std::string &path );
	GLuint LoadFragmentShader( const std::string &path );
	GLuint LoadShader( const GLenum type, const std::string &path );

	GLuint CreateShader( const GLenum type, const std::string &src );

	bool InterfaceSetup( std::shared_ptr< CShaderProgram > shaderProgram );

	void RegisterUniformBuffer( const std::shared_ptr< CUniformBuffer > &ubo );

	const CFileSystem &m_filesystem;

	std::unordered_map< std::string, std::weak_ptr< CShaderProgram > > m_programs;

	std::unordered_map< std::string, GLuint > m_vertexShaders;
	std::unordered_map< std::string, GLuint > m_fragmentShaders;

	std::unordered_set< std::shared_ptr< CUniformBuffer > > m_registeredUniformBuffers;

	static const std::string srcAdditionShaderVersion;
	static const std::string srcAdditionVsShaderExtensions;
	static const std::string srcAdditionFsShaderExtensions;

	static const std::unordered_map< GLint, SShaderInterface > allowedAttributes;

	static const std::map< EReservedUniformLocations, SShaderInterface > reservedUniforms;

	std::shared_ptr< CShaderProgram > m_dummyProgram;
};

#endif // CSHADERMANAGER_HPP
