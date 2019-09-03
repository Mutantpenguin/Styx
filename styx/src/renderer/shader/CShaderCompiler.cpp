#include "CShaderCompiler.hpp"

#include <glbinding-aux/Meta.h>

#include "src/renderer/GLHelper.hpp"

#include "src/logger/CLogger.hpp"

const std::string CShaderCompiler::srcAdditionShaderVersion = "#version 430\n";

const std::map<const AttributeLocation, const SShaderInterface> CShaderCompiler::AllowedAttributes = {	{ AttributeLocation::position,		{ "position",	GLHelper::glmTypeToGLSLType<glm::vec3>() } },
																										{ AttributeLocation::normal,		{ "normal",		GLHelper::glmTypeToGLSLType<glm::vec3>() } },
																										{ AttributeLocation::tangent,		{ "tangent",	GLHelper::glmTypeToGLSLType<glm::vec3>() } },
																										{ AttributeLocation::bitangent,	{ "bitangent",	GLHelper::glmTypeToGLSLType<glm::vec3>() } },
																										{ AttributeLocation::color,		{ "color",		GLHelper::glmTypeToGLSLType<glm::vec3>() } },
																										{ AttributeLocation::uv0,			{ "uv0",		GLHelper::glmTypeToGLSLType<glm::vec2>() } },
																										{ AttributeLocation::uv1,			{ "uv1",		GLHelper::glmTypeToGLSLType<glm::vec2>() } },
																										{ AttributeLocation::uv2,			{ "uv2",		GLHelper::glmTypeToGLSLType<glm::vec2>() } },
																										{ AttributeLocation::uv3,			{ "uv3",		GLHelper::glmTypeToGLSLType<glm::vec2>() } } };

const std::unordered_map<EEngineUniform, const SShaderInterface> CShaderCompiler::EngineUniforms = {	{ EEngineUniform::modelViewProjectionMatrix,	{ "modelViewProjectionMatrix",	GLHelper::glmTypeToGLSLType<glm::mat4>() } },
																										{ EEngineUniform::modelViewMatrix,				{ "modelViewMatrix",			GLHelper::glmTypeToGLSLType<glm::mat4>() } },
																										{ EEngineUniform::modelMatrix,					{ "modelMatrix",				GLHelper::glmTypeToGLSLType<glm::mat4>() } } };


const std::string CShaderCompiler::DummyVertexShaderBody = fmt::format( R"glsl(
void main()
{{
	gl_Position = {0} * vec4( {1}, 1 );
}}
)glsl", CShaderCompiler::EngineUniforms.at( EEngineUniform::modelViewProjectionMatrix ).name, CShaderCompiler::AllowedAttributes.at( AttributeLocation::position ).name );

const std::string CShaderCompiler::DummyGeometryShaderBody = R"glsl(
void main()
{
	gl_Position = gl_in[ 0 ].gl_Position;
	EmitVertex();

	EndPrimitive();
}
)glsl";

const std::string CShaderCompiler::DummyFragmentShaderBody = R"glsl(
out vec4 color;
void main()
{
	color = vec4( 1, 0, 1, 1 ).rgba;
}
)glsl";

CShaderCompiler::CShaderCompiler()
{
	if( !Compile( m_dummyVertexShader, GL_VERTEX_SHADER, DummyVertexShaderBody ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create dummy vertex shader" );
	}

	if( !Compile( m_dummyGeometryShader, GL_GEOMETRY_SHADER, DummyGeometryShaderBody ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create dummy geometry shader" );
	}

	if( !Compile( m_dummyFragmentShader, GL_FRAGMENT_SHADER, DummyFragmentShaderBody ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create dummy fragment shader" );
	}
}

void CShaderCompiler::RegisterUniformBuffer( const std::shared_ptr<const CUniformBuffer> &ubo )
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

	case GL_GEOMETRY_SHADER:
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
		std::vector<char> errorMessage( infoLogLength );
		glGetShaderInfoLog( shader->GLID, infoLogLength, nullptr, errorMessage.data() );

		logWARNING( "Error compiling shader: {0}", errorMessage.data() );

		shader->Reset();

		return( false );
	}

	return( true );
}

const std::shared_ptr<const CShader> CShaderCompiler::DummyVertexShader() const
{
	return( m_dummyVertexShader );
}

const std::shared_ptr<const CShader> CShaderCompiler::DummyGeometryShader() const
{
	return( m_dummyGeometryShader );
}

const std::shared_ptr<const CShader> CShaderCompiler::DummyFragmentShader() const
{
	return( m_dummyFragmentShader );
}