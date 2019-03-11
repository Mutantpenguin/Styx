#include "CShaderCompiler.hpp"

#include <glbinding-aux/Meta.h>

#include "src/renderer/GLHelper.hpp"

#include "src/logger/CLogger.hpp"

const std::string CShaderCompiler::srcAdditionShaderVersion = "#version 430\n";

const std::map< const CVAO::EAttributeLocation, const SShaderInterface > CShaderCompiler::AllowedAttributes = { { CVAO::EAttributeLocation::position,	{ "position",	GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																											    { CVAO::EAttributeLocation::normal,		{ "normal",		GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																											    { CVAO::EAttributeLocation::texcoord,	{ "texcoord",	GLHelper::glmTypeToGLSLType< glm::vec2 >() } },
																											    { CVAO::EAttributeLocation::tangent,	{ "tangent",	GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																											    { CVAO::EAttributeLocation::bitangent,	{ "bitangent",	GLHelper::glmTypeToGLSLType< glm::vec3 >() } } };

const std::unordered_map< EEngineUniform, const SShaderInterface > CShaderCompiler::EngineUniforms = { { EEngineUniform::modelViewProjectionMatrix,	{ "modelViewProjectionMatrix",	GLHelper::glmTypeToGLSLType< glm::mat4 >() } },
																									   { EEngineUniform::modelMatrix,				{ "modelMatrix",				GLHelper::glmTypeToGLSLType< glm::mat4 >() } } };


void CShaderCompiler::RegisterUniformBuffer( const std::shared_ptr< const CUniformBuffer > &ubo )
{
	m_registeredUniformBuffers.insert( ubo );
}

bool CShaderCompiler::Compile( const std::shared_ptr<CShader> &shader, const GLenum type, const std::string &body ) const
{
	std::string source = srcAdditionShaderVersion;

	switch( type )
	{
	case GL_VERTEX_SHADER:
		source += "\n";

		for( const auto &[ location, interface ] : AllowedAttributes )
		{
			source += fmt::format( "layout( location = {0} ) in {1} {2};", static_cast<GLint>( location ), GLHelper::GLSLTypeToString( interface.type ), interface.name ) + "\n";
		}

		break;

	case GL_FRAGMENT_SHADER:
		break;

	default:
		logWARNING( "unsupported shader type '{0}'", glbinding::aux::Meta::getString( type ) );
		return( false );
	}

	if( !EngineUniforms.empty() )
	{
		source += "\n";

		for( const auto &[ _, interface ] : EngineUniforms )
		{
			source += fmt::format( "uniform {0} {1};", GLHelper::GLSLTypeToString( interface.type ), interface.name ) + "\n";
		}
	}

	if( !m_registeredUniformBuffers.empty() )
	{
		source += "\n";

		for( const auto &ubo : m_registeredUniformBuffers )
		{
			source += ubo->Source() + "\n";
		}
	}

	source += "\n" + body;

	shader->GLID = glCreateShader( type );

	if( 0 == shader->GLID )
	{
		logWARNING( "Error creating shader object" );
		return( false );
	}

	{
		const char *tempConstSrc = source.c_str();
		glShaderSource( shader->GLID, 1, &tempConstSrc, nullptr );
	}

	glCompileShader( shader->GLID );

	GLint compileResult;
	glGetShaderiv( shader->GLID, GL_COMPILE_STATUS, &compileResult );

	if( compileResult != static_cast<GLint>( GL_TRUE ) )
	{
		int infoLogLength;
		glGetShaderiv( shader->GLID, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector< char > errorMessage( infoLogLength );
		glGetShaderInfoLog( shader->GLID, infoLogLength, nullptr, errorMessage.data() );

		logWARNING( "Error compiling shader: {0}", errorMessage.data() );

		return( false );
	}

	return( true );
}