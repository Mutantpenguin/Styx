#include "CShaderManager.hpp"

#include <glbinding/Meta.h>

#include "../CCamera.hpp"
#include "../GLHelper.hpp"
#include "../CVAO.hpp"

#include "../../logger/CLogger.hpp"

constexpr const GLint CShaderManager::requiredCombinedTextureImageUnits;

const std::string CShaderManager::srcAdditionShaderVersion = "#version 410\n";

const std::string CShaderManager::srcAdditionVsShaderExtensions =	"#extension " + glbinding::Meta::getString( GLextension::GL_ARB_explicit_uniform_location ) + " : require\n" \
																	"#extension " + glbinding::Meta::getString( GLextension::GL_ARB_shading_language_420pack ) + " : require\n";

const std::string CShaderManager::srcAdditionFsShaderExtensions =	"#extension " + glbinding::Meta::getString( GLextension::GL_ARB_explicit_uniform_location ) + " : require\n" \
																	"#extension " + glbinding::Meta::getString( GLextension::GL_ARB_shading_language_420pack ) + " : require\n";

const std::unordered_map< GLint, SShaderInterface > CShaderManager::allowedAttributes = {	{ CVAO::attributeLocationVertex,	{ "vertex",		GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																							{ CVAO::attributeLocationNormal,	{ "normal",		GLHelper::glmTypeToGLSLType< glm::vec3 >() } },
																							{ CVAO::attributeLocationTexcoord,	{ "texcoord",	GLHelper::glmTypeToGLSLType< glm::vec2 >() } } };

// TODO use map, because unordered_map needs manual work to work with enums
const std::map< EReservedUniformLocations, SShaderInterface > CShaderManager::reservedUniforms = {	{ EReservedUniformLocations::modelViewProjectionMatrix,	{ "modelViewProjectionMatrix",	GLHelper::glmTypeToGLSLType< glm::mat4 >() } },
																									{ EReservedUniformLocations::textureMatrix,				{ "textureMatrix",				GLHelper::glmTypeToGLSLType< glm::mat3 >() } },
																									{ EReservedUniformLocations::modelMatrix,				{ "modelMatrix",				GLHelper::glmTypeToGLSLType< glm::mat4 >() } } };

CShaderManager::CShaderManager( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
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

bool CShaderManager::Init( void )
{
	if( !CreateDummyProgram() )
	{
		return( false );
	}

	return( true );
}

bool CShaderManager::CreateDummyProgram( void )
{
	const std::string vertexShaderSrc = "layout( location = 0 ) in vec3 vertex;" \
										"layout( location = 0 ) uniform mat4 modelViewProjectionMatrix;" \
										"void main()" \
										"{" \
										"	gl_Position = modelViewProjectionMatrix * vec4( vertex, 1 );" \
										"}";

	const GLuint vertexShader = CreateShader( GL_VERTEX_SHADER, vertexShaderSrc );
	if( 0 == vertexShader )
	{
		LOG( logERROR ) << "couldn't create dummy vertex shader";
		return( false );
	}

	const std::string fragmentShaderSrc = 	"in vec2 UV;" \
											"out vec4 color;" \
											"void main()" \
											"{" \
											"	color = vec4( 1, 0, 1, 1 ).rgba;" \
											"}";

	const GLuint fragmentShader = CreateShader( GL_FRAGMENT_SHADER, fragmentShaderSrc );
	if( 0 == fragmentShader )
	{
		LOG( logERROR ) << "couldn't create dummy fragment shader";
		return( false );
	}

	const GLuint program = CreateProgram( vertexShader, fragmentShader );
	if( 0 == program )
	{
		LOG( logERROR ) << "couldn't create dummy program";
		return( false );
	}

	std::shared_ptr< CShaderProgram > shaderProgram = std::make_shared< CShaderProgram >( program );

	if( !InterfaceSetup( shaderProgram ) )
	{
		LOG( logWARNING ) << "dummy program object is not valid";
		return( false );
	}

	m_dummyProgram = shaderProgram;

	return( true );
}

std::shared_ptr< CShaderProgram > CShaderManager::GetDummyShader( void ) const
{
	return( m_dummyProgram );
}

std::shared_ptr< CShaderProgram > CShaderManager::LoadProgram( const std::string &pathVertexShader, const std::string &pathFragmentShader )
{
	const std::string programIdentifier = pathVertexShader + "|" + pathFragmentShader;

	auto it = m_programs.find( programIdentifier );
	if( m_programs.end() != it )
	{
		return( it->second.lock() );
	}
	else
	{
		const GLuint vertexShader 	= LoadVertexShader( pathVertexShader );
		if( 0 == vertexShader )
		{
			return( m_dummyProgram );
		}

		const GLuint fragmentShader	= LoadFragmentShader( pathFragmentShader );
		if( 0 == fragmentShader )
		{
			return( m_dummyProgram );
		}

		const GLuint program = CreateProgram( vertexShader, fragmentShader );
		if( 0 == program )
		{
			return( m_dummyProgram );
		}

		std::shared_ptr< CShaderProgram > shaderProgram = std::make_shared< CShaderProgram >( program );

		if( !InterfaceSetup( shaderProgram ) )
		{
			LOG( logWARNING ) << "program object is not valid";
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
		LOG( logWARNING ) << "Error creating program object";
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

		LOG( logWARNING ) << "Error linking program: " << errorMessage.data();

		glDeleteProgram( program );

		return( 0 );
	}

	return( program );
}

GLuint CShaderManager::LoadVertexShader( const std::string &path )
{
	auto it = m_vertexShaders.find( path );
	if( m_vertexShaders.end() != it )
	{
		return( it->second );
	}
	else
	{
		GLuint vertexShader = LoadShader( GL_VERTEX_SHADER, path );
		if( 0 == vertexShader )
		{
			LOG( logERROR ) << "couldn't create vertex shader from '" << path << "'";
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
	auto it = m_fragmentShaders.find( path );
	if( m_fragmentShaders.end() != it )
	{
		return( it->second );
	}
	else
	{
		GLuint fragmentShader = LoadShader( GL_FRAGMENT_SHADER, path );
		if( 0 == fragmentShader )
		{
			LOG( logERROR ) << "couldn't create fragment shader from '" << path << "'";
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
		LOG( logWARNING ) << "'" << path << "' does not exist";
		return( 0 );
	}
	else
	{
		return( CreateShader( type, m_filesystem.LoadTextFileToBuffer( path ) ) );
	}
}

GLuint CShaderManager::CreateShader( const GLenum type, const std::string &src )
{
	std::string source;

	switch( type )
	{
		case GL_VERTEX_SHADER:
			source =	srcAdditionShaderVersion +
						srcAdditionVsShaderExtensions +
						src;
			break;

		case GL_FRAGMENT_SHADER:
			source =	srcAdditionShaderVersion +
						srcAdditionFsShaderExtensions +
						src;
			break;

		default:
			LOG( logWARNING ) << "unsupported shader type '" << glbinding::Meta::getString( type ) << "'";
			return( 0 );
	}

	for( const std::shared_ptr< const CUniformBuffer > ubo : m_registeredUniformBuffers )
	{
		const size_t uniformBlockPosition = source.find( ubo->Placeholder() );
		if( std::string::npos != uniformBlockPosition )
		{
			source.replace( uniformBlockPosition, ubo->Placeholder().length(), ubo->Source() );
		}
	}

	const GLuint shader = glCreateShader( type );

	if( 0 == shader )
	{
		LOG( logWARNING ) << "Error creating shader object";
		return( 0 );
	}

	const char *shaderSrc = source.c_str();
	glShaderSource( shader, 1, &shaderSrc, nullptr );
	glCompileShader( shader );

	GLint compileResult;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compileResult );

	if( compileResult != static_cast< GLint>( GL_TRUE ) )
	{
		int infoLogLength;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector< char > errorMessage( infoLogLength );
		glGetShaderInfoLog( shader, infoLogLength, nullptr, errorMessage.data() );

		LOG( logWARNING ) << "Error compiling shader: " << errorMessage.data();

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

	for( int attribIndex = 0; attribIndex < numActiveAttributes; ++attribIndex )
	{
		GLint values[ attributeProperties.size() ];
		glGetProgramResourceiv( shaderProgram->m_program, GL_PROGRAM_INPUT, attribIndex, attributeProperties.size(), attributeProperties.data(), attributeProperties.size(), NULL, values );

		const GLint attributeLocation = values[ 2 ];

		auto attributeIt = allowedAttributes.find( attributeLocation );
		if( allowedAttributes.end() == attributeIt )
		{
			LOG( logERROR ) << "attribute location '" << attributeLocation << "' is not allowed";
			return( false );
		}
		else
		{
			std::vector< char > nameData( values[ 1 ] );
			glGetProgramResourceName( shaderProgram->m_program, GL_PROGRAM_INPUT, attribIndex, nameData.size(), nullptr, &nameData[ 0 ] );
			std::string attributeName( nameData.data() );

			const GLenum attributeType = static_cast< GLenum>( values[ 0 ] );
			const SShaderInterface &attributeInterface = attributeIt->second;
			if( ( attributeInterface.name != attributeName )
				||
				( attributeInterface.type != attributeType ) )
			{
				LOG( logERROR ) << "attribute '" << attributeName << "' with type " << glbinding::Meta::getString( attributeType ) << " is not allowed at location '" << attributeLocation << "'";
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

	for( int uniformIndex = 0; uniformIndex < numActiveUniforms; ++uniformIndex )
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
				shaderProgram->m_requiredTextures[ uniformLocation ] = { uniformName, uniformType };
				if( shaderProgram->m_requiredTextures.size() > CShaderManager::requiredCombinedTextureImageUnits )
				{
					LOG( logERROR ) << "uses " << shaderProgram->m_requiredTextures.size() << " samplers but only " << CShaderManager::requiredCombinedTextureImageUnits << "are allowed";
					return( false );
				}
				break;

			case GL_FLOAT_MAT3:
			case GL_FLOAT_MAT4:
			case GL_FLOAT_VEC3:
			case GL_FLOAT_VEC4:
			case GL_UNSIGNED_INT:
			case GL_INT:
				{
					const EReservedUniformLocations uniformLocationEnum = static_cast< EReservedUniformLocations >( uniformLocation );

					auto uniformIt = reservedUniforms.find( uniformLocationEnum );
					if( reservedUniforms.end() == uniformIt )
					{
						shaderProgram->m_requiredInstanceUniforms[ uniformLocation ] = { uniformName, uniformType };
					}
					else
					{
						const SShaderInterface &uniformInterface = uniformIt->second;
						if( ( uniformInterface.name != uniformName )
							||
							( uniformInterface.type != uniformType ) )
						{
							LOG( logERROR ) << "uniform '" << uniformName << "' with type " << glbinding::Meta::getString( uniformType ) << " is not allowed at location '" << uniformLocation << "'";
							return( false );
						}
						else
						{
							shaderProgram->m_requiredReservedUniforms.push_back( uniformLocationEnum );
						}
					}
					break;
				}

			default:
				LOG( logERROR ) << "unsupported uniform type " << glbinding::Meta::getString( uniformType ) << " for uniform '" << uniformName << "' at location " << uniformLocation;
				return( false );
		}
	}

	return( true );
}

void CShaderManager::RegisterUniformBuffer( const std::shared_ptr< CUniformBuffer > &ubo )
{
	m_registeredUniformBuffers.insert( ubo );
}
