#include "CShaderManager.hpp"

#include <algorithm>

#include <glbinding/Meta.h>

#include "src/engine/renderer/camera/CCamera.hpp"
#include "src/engine/renderer/GLHelper.hpp"

#include "src/engine/logger/CLogger.hpp"

constexpr const GLint CShaderManager::requiredCombinedTextureImageUnits;

const std::string CShaderManager::srcAdditionShaderVersion = "#version 410\n";

// TODO not needed anymore when we can switch to a 4.2 core context (or higher)
const std::string CShaderManager::srcAdditionVsShaderExtensions =	"#extension " + glbinding::Meta::getString( GLextension::GL_ARB_shading_language_420pack ) + " : require\n";
const std::string CShaderManager::srcAdditionFsShaderExtensions =	"#extension " + glbinding::Meta::getString( GLextension::GL_ARB_shading_language_420pack ) + " : require\n";

const std::map< const CVAO::EAttributeLocation, const SShaderInterface > CShaderManager::allowedAttributes = {	{ CVAO::EAttributeLocation::vertex,		{ "vertex",		GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																												{ CVAO::EAttributeLocation::normal,		{ "normal",		GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																												{ CVAO::EAttributeLocation::texcoord,	{ "texcoord",	GLHelper::glmTypeToGLSLType< glm::vec2 >() } } };

const std::unordered_map< const EEngineUniform, const SShaderInterface > CShaderManager::engineUniforms = {	{ EEngineUniform::modelViewProjectionMatrix,	{ "modelViewProjectionMatrix",	GLHelper::glmTypeToGLSLType< glm::mat4 >() } },
																											{ EEngineUniform::modelMatrix,					{ "modelMatrix",				GLHelper::glmTypeToGLSLType< glm::mat4 >() } } };

CShaderManager::CShaderManager( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
	if( !CreateDummyProgram() )
	{
		throw Exception();
	}
}

CShaderManager::~CShaderManager()
{
	for( const auto &vertexShader : m_vertexShaders )
	{
		glDeleteShader( vertexShader.second );
	}
	m_vertexShaders.clear();

	for( const auto &fragmentShader : m_fragmentShaders )
	{
		glDeleteShader( fragmentShader.second );
	}
	m_fragmentShaders.clear();
}

bool CShaderManager::CreateDummyProgram( void )
{
	const auto vertexAttribute = allowedAttributes.at( CVAO::EAttributeLocation::vertex );
	const auto uniformModelViewProjectionMatrix = engineUniforms.at( EEngineUniform::modelViewProjectionMatrix );

	const std::string vertexShaderBody = "void main()" \
										"{" \
										"	gl_Position = " + uniformModelViewProjectionMatrix.name + " * vec4( " + vertexAttribute.name + ", 1 );" \
										"}";

	const GLuint vertexShader = CreateShader( GL_VERTEX_SHADER, vertexShaderBody );
	if( 0 == vertexShader )
	{
		logERROR( "couldn't create dummy vertex shader" );
		return( false );
	}

	const std::string fragmentShaderBody = 	"out vec4 color;" \
											"void main()" \
											"{" \
											"	color = vec4( 1, 0, 1, 1 ).rgba;" \
											"}";

	const GLuint fragmentShader = CreateShader( GL_FRAGMENT_SHADER, fragmentShaderBody );
	if( 0 == fragmentShader )
	{
		logERROR( "couldn't create dummy fragment shader" );
		return( false );
	}

	const GLuint program = CreateProgram( vertexShader, fragmentShader );
	if( 0 == program )
	{
		logERROR( "couldn't create dummy program" );
		return( false );
	}

	m_dummyProgram = std::make_shared< CShaderProgram >( program );

	if( !InterfaceSetup( m_dummyProgram ) )
	{
		logWARNING( "dummy program object is not valid" );
		return( false );
	}

	return( true );
}

std::shared_ptr< CShaderProgram > CShaderManager::GetDummyShader( void ) const
{
	return( m_dummyProgram );
}

std::shared_ptr< CShaderProgram > CShaderManager::LoadProgram( const std::string &pathVertexShader, const std::string &pathFragmentShader )
{
	const std::string programIdentifier = pathVertexShader + "|" + pathFragmentShader;

	const auto it = m_programs.find( programIdentifier );
	if( m_programs.end() != it )
	{
		return( it->second );
	}
	else
	{
		const GLuint vertexShader = LoadVertexShader( pathVertexShader );
		if( 0 == vertexShader )
		{
			logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", pathVertexShader, pathFragmentShader );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		const GLuint fragmentShader = LoadFragmentShader( pathFragmentShader );
		if( 0 == fragmentShader )
		{
			logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", pathVertexShader, pathFragmentShader );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		const GLuint program = CreateProgram( vertexShader, fragmentShader );
		if( 0 == program )
		{
			logWARNING( "program object from vertex shader '{0}' and fragment shader '{1}' is not valid", pathVertexShader, pathFragmentShader );
			logWARNING( "using dummy shader" );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		auto shaderProgram = std::make_shared< CShaderProgram >( program );

		if( !InterfaceSetup( shaderProgram ) )
		{
			logWARNING( "unable to setup the interface for the program object from vertex shader '{0}' and fragment shader '{1}'", pathVertexShader, pathFragmentShader );
			logWARNING( "using dummy shader" );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		m_programs[ programIdentifier ] = shaderProgram;

		return( shaderProgram );
	}
}

GLuint CShaderManager::CreateProgram( const GLuint vertexShader, const GLuint fragmentShader )
{
	const GLuint program = glCreateProgram();
	if( 0 == program )
	{
		logWARNING( "Error creating program object" );
		return( 0 );
	}

	glAttachShader( program, vertexShader );
	glAttachShader( program, fragmentShader );

	glLinkProgram( program );

	GLint compileResult;
	glGetProgramiv( program, GL_LINK_STATUS, &compileResult );

	if( compileResult != static_cast< GLint>( GL_TRUE ) )
	{
		int infoLogLength;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector< char > errorMessage( infoLogLength );
		glGetProgramInfoLog( program, infoLogLength, nullptr, errorMessage.data() );

		logWARNING( "Error linking program: {0}", errorMessage.data() );

		glDeleteProgram( program );

		return( 0 );
	}

	return( program );
}

GLuint CShaderManager::LoadVertexShader( const std::string &path )
{
	const auto it = m_vertexShaders.find( path );
	if( m_vertexShaders.end() != it )
	{
		return( it->second );
	}
	else
	{
		const GLuint vertexShader = LoadShader( GL_VERTEX_SHADER, path );
		if( 0 == vertexShader )
		{
			logERROR( "couldn't create vertex shader from '{0}'", path );

			// TODO do the same as with the program object? -> store and use the dummy shader from here on, so future compiles don't need to be made if we know it will fail
			return( 0 );
		}
		else
		{
			m_vertexShaders[ path ] = vertexShader;
			return( vertexShader );
		}
	}
}

GLuint CShaderManager::LoadFragmentShader( const std::string &path )
{
	const auto it = m_fragmentShaders.find( path );
	if( m_fragmentShaders.end() != it )
	{
		return( it->second );
	}
	else
	{
		const GLuint fragmentShader = LoadShader( GL_FRAGMENT_SHADER, path );
		if( 0 == fragmentShader )
		{
			logERROR( "couldn't create fragment shader from '{0}'", path );

			// TODO do the same as with the program object? -> store and use the dummy shader from here on, so future compiles don't need to be made if we know it will fail
			return( 0 );
		}
		else
		{
			m_fragmentShaders[ path ] = fragmentShader;
			return( fragmentShader );
		}
	}
}

GLuint CShaderManager::LoadShader( const GLenum type, const std::string &path )
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
		return( 0 );
	}
	else
	{
		return( CreateShader( type, m_filesystem.LoadFileToString( path ) ) );
	}
}

GLuint CShaderManager::CreateShader( const GLenum type, const std::string &body )
{
	std::string source;

	switch( type )
	{
		case GL_VERTEX_SHADER:
			source =	srcAdditionShaderVersion +
						srcAdditionVsShaderExtensions;

			source += "\n";

			// TODO this will work with -std=c++1z;
			// for( const auto && [ location, interface ] : allowedAttributes )
			for( const auto &attribute : allowedAttributes )
			{
				source += fmt::format( "layout( location = {0} ) in {1} {2};", static_cast< GLint >( attribute.first ), GLHelper::GLSLTypeToString( attribute.second.type ), attribute.second.name ) + "\n";
			}

			break;

		case GL_FRAGMENT_SHADER:
			source =	srcAdditionShaderVersion +
						srcAdditionFsShaderExtensions;
			break;

		default:
			logWARNING( "unsupported shader type '{0}'", glbinding::Meta::getString( type ) );
			return( 0 );
	}

	if( !engineUniforms.empty() )
	{
		source += "\n";

		for( const auto &engineUniform : engineUniforms )
		{
			source += fmt::format( "uniform {0} {1};", GLHelper::GLSLTypeToString( engineUniform.second.type ), engineUniform.second.name ) + "\n";
		}
	}

	if( !m_registeredUniformBuffers.empty() )
	{
		source += "\n";

		for( const std::shared_ptr< const CUniformBuffer > ubo : m_registeredUniformBuffers )
		{
			source += ubo->Source() + "\n";
		}
	}

	source += "\n" + body;

	const GLuint shader = glCreateShader( type );

	if( 0 == shader )
	{
		logWARNING( "Error creating shader object" );
		return( 0 );
	}

	{
		const char *tempConstSrc = source.c_str();
		glShaderSource( shader, 1, &tempConstSrc, nullptr );
	}

	glCompileShader( shader );

	GLint compileResult;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compileResult );

	if( compileResult != static_cast< GLint>( GL_TRUE ) )
	{
		int infoLogLength;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector< char > errorMessage( infoLogLength );
		glGetShaderInfoLog( shader, infoLogLength, nullptr, errorMessage.data() );

		logWARNING( "Error compiling shader: {0}", errorMessage.data() );

		return( 0 );
	}

	return( shader );
}

bool CShaderManager::InterfaceSetup( std::shared_ptr< CShaderProgram > shaderProgram )
{
	/*
	 * active attributes
	 */
	GLint numActiveAttributes = 0;
	glGetProgramInterfaceiv( shaderProgram->m_program, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttributes );
	const std::array< GLenum, 3 > attributeProperties { { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint attribIndex = 0; attribIndex < numActiveAttributes; ++attribIndex )
	{
		GLint values[ attributeProperties.size() ];
		glGetProgramResourceiv( shaderProgram->m_program, GL_PROGRAM_INPUT, attribIndex, attributeProperties.size(), attributeProperties.data(), attributeProperties.size(), NULL, values );

		const GLint attributeLocation = values[ 2 ];

		const auto attributeIt = allowedAttributes.find( static_cast< CVAO::EAttributeLocation >( attributeLocation ) );
		if( allowedAttributes.end() == attributeIt )
		{
			logERROR( "attribute location '{0}' is not allowed", attributeLocation );
			return( false );
		}
		else
		{
			std::vector< char > nameData( values[ 1 ] );
			glGetProgramResourceName( shaderProgram->m_program, GL_PROGRAM_INPUT, attribIndex, nameData.size(), nullptr, &nameData[ 0 ] );
			const std::string attributeName( nameData.data() );

			const GLenum attributeType = static_cast< GLenum>( values[ 0 ] );
			const SShaderInterface &attributeInterface = attributeIt->second;
			if( ( attributeInterface.name != attributeName )
				||
				( attributeInterface.type != attributeType ) )
			{
				logERROR( "attribute '{0}' with type {1} is not allowed at location '{2}'", attributeName, glbinding::Meta::getString( attributeType ), attributeLocation );
				return( false );
			}
		}
	}

	/*
	 * active non-block uniforms
	 */
	GLint numActiveUniforms = 0;
	glGetProgramInterfaceiv( shaderProgram->m_program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms );
	const std::array< GLenum, 4 > uniformProperties { { GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint uniformIndex = 0; uniformIndex < numActiveUniforms; ++uniformIndex )
	{
		GLint values[ uniformProperties.size() ];
		glGetProgramResourceiv( shaderProgram->m_program, GL_UNIFORM, uniformIndex, uniformProperties.size(), uniformProperties.data(), uniformProperties.size(), nullptr, &values[ 0 ] );

		// skip any uniforms that are in a block.
		if( values[ 0 ] != -1 )
		{
			continue;
		}

		std::vector< char > nameData( values[ 2 ] );
		glGetProgramResourceName( shaderProgram->m_program, GL_UNIFORM, uniformIndex, nameData.size(), NULL, &nameData[ 0 ] );
		std::string uniformName( nameData.data() );

		const GLint  uniformLocation = values[ 3 ];
		const GLenum uniformType = static_cast< GLenum>( values[ 1 ] );

		switch( uniformType )
		{
			case GL_SAMPLER_2D:
			case GL_SAMPLER_CUBE:
			case GL_SAMPLER_2D_ARRAY:
				shaderProgram->m_requiredSamplers[ uniformLocation ] = { uniformName, uniformType };
				if( shaderProgram->m_requiredSamplers.size() > CShaderManager::requiredCombinedTextureImageUnits )
				{
					logERROR( "uses {0} samplers but max {1} are allowed", shaderProgram->m_requiredSamplers.size(), CShaderManager::requiredCombinedTextureImageUnits );
					return( false );
				}
				break;

			case GL_FLOAT_MAT3:
			case GL_FLOAT_MAT4:
			case GL_FLOAT_VEC2:
			case GL_FLOAT_VEC3:
			case GL_FLOAT_VEC4:
			case GL_UNSIGNED_INT:
			case GL_INT:
			case GL_FLOAT:
				{
					const auto engineUniformIt = std::find_if(	std::cbegin( engineUniforms ),
																std::cend( engineUniforms ),
																[&]( const auto &uniform )
																{
																	return( uniform.second.name == uniformName );
																} );

					if( std::cend( engineUniforms ) != engineUniformIt )
					{
						// uniform gets provided by the engine

						const SShaderInterface &uniformInterface = engineUniformIt->second;
						if( uniformInterface.type != uniformType )
						{
							logERROR( "uniform '{0}' needs to be of type '{1}' but was declared as '{2}'", uniformName, glbinding::Meta::getString( uniformInterface.type ), glbinding::Meta::getString( uniformType ) );
							return( false );
						}
						else
						{
							shaderProgram->m_requiredEngineUniforms[ uniformLocation ] = engineUniformIt->first;
						}
					}
					else
					{
						// uniform gets provided by the material

						shaderProgram->m_requiredMaterialUniforms[ uniformLocation ] = { uniformName, uniformType };
					}
					break;
				}

			default:
				logERROR( "unsupported uniform type {0} for uniform '{1}'", glbinding::Meta::getString( uniformType ), uniformName );
				return( false );
		}
	}

	return( true );
}

void CShaderManager::RegisterUniformBuffer( const std::shared_ptr< const CUniformBuffer > &ubo )
{
	m_registeredUniformBuffers.insert( ubo );
}
