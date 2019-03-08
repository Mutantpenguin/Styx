#include "CShaderManager.hpp"

#include <algorithm>

#include <glbinding-aux/Meta.h>

#include "src/logger/CLogger.hpp"

constexpr const GLint CShaderManager::requiredCombinedTextureImageUnits;

CShaderManager::CShaderManager( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler ) :
	m_filesystem { p_filesystem },
	m_shaderCompiler { shaderCompiler }
{
	if( !CreateDummyProgram() )
	{
		throw Exception();
	}

	logINFO( "shader manager was initialized" );
}

CShaderManager::~CShaderManager()
{
	logINFO( "shader manager is shutting down" );

	for( const auto &shader : m_shaders )
	{
		glDeleteShader( shader.second );
	}
	m_shaders.clear();
}

bool CShaderManager::CreateDummyProgram()
{
	const auto &positionAttribute = CShaderCompiler::AllowedAttributes.at( CVAO::EAttributeLocation::position );
	const auto &uniformModelViewProjectionMatrix = CShaderCompiler::EngineUniforms.at( EEngineUniform::modelViewProjectionMatrix );

	const std::string vertexShaderString =	"void main()" \
											"{" \
											"	gl_Position = " + uniformModelViewProjectionMatrix.name + " * vec4( " + positionAttribute.name + ", 1 );" \
											"}";

	const GLuint vertexShader = m_shaderCompiler.Compile( GL_VERTEX_SHADER, vertexShaderString );
	if( 0 == vertexShader )
	{
		logERROR( "couldn't create dummy vertex shader" );
		return( false );
	}

	const std::string fragmentShaderString = 	"out vec4 color;" \
												"void main()" \
												"{" \
												"	color = vec4( 1, 0, 1, 1 ).rgba;" \
												"}";

	const GLuint fragmentShader = m_shaderCompiler.Compile( GL_FRAGMENT_SHADER, fragmentShaderString );
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

const std::shared_ptr< const CShaderProgram > CShaderManager::GetDummyShader() const
{
	return( m_dummyProgram );
}

const std::shared_ptr< const CShaderProgram > CShaderManager::LoadProgram( const std::string &pathVertexShader, const std::string &pathFragmentShader )
{
	const std::string programIdentifier = pathVertexShader + "|" + pathFragmentShader;

	const auto it = m_programs.find( programIdentifier );
	if( std::end( m_programs ) != it )
	{
		return( it->second );
	}
	else
	{
		const GLuint vertexShader = LoadShader( GL_VERTEX_SHADER, pathVertexShader );
		if( 0 == vertexShader )
		{
			logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", pathVertexShader, pathFragmentShader );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		const GLuint fragmentShader = LoadShader( GL_FRAGMENT_SHADER, pathFragmentShader );
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

const std::shared_ptr< const CShaderProgram > CShaderManager::CreateProgramFromStrings( const std::string &vertexShaderString, const std::string &fragmentShaderString ) const
{
	const GLuint vertexShader = m_shaderCompiler.Compile( GL_VERTEX_SHADER, vertexShaderString );
	if( 0 == vertexShader )
	{
		logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", vertexShaderString, fragmentShaderString );
		return( m_dummyProgram );
	}

	const GLuint fragmentShader = m_shaderCompiler.Compile( GL_FRAGMENT_SHADER, fragmentShaderString );
	if( 0 == fragmentShader )
	{
		logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", vertexShaderString, fragmentShaderString );
		return( m_dummyProgram );
	}

	const GLuint program = CreateProgram( vertexShader, fragmentShader );
	if( 0 == program )
	{
		logWARNING( "program object from vertex shader '{0}' and fragment shader '{1}' is not valid", vertexShaderString, fragmentShaderString );
		logWARNING( "using dummy shader" );
		return( m_dummyProgram );
	}

	auto shaderProgram = std::make_shared< CShaderProgram >( program );

	if( !InterfaceSetup( shaderProgram ) )
	{
		logWARNING( "unable to setup the interface for the program object from vertex shader '{0}' and fragment shader '{1}'", vertexShaderString, fragmentShaderString );
		logWARNING( "using dummy shader" );
		return( m_dummyProgram );
	}

	return( shaderProgram );
}

GLuint CShaderManager::CreateProgram( const GLuint vertexShader, const GLuint fragmentShader ) const
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

GLuint CShaderManager::LoadShader( GLenum type, const std::string &path )
{
	const auto it = m_shaders.find( path );
	if( std::end( m_shaders ) != it )
	{
		return( it->second );
	}
	else
	{
		if( !m_filesystem.Exists( path ) )
		{
			logWARNING( "shader file '{0}' does not exist", path );
			return( 0 );
		}
		else
		{
			const GLuint shader = m_shaderCompiler.Compile( type, m_filesystem.LoadFileToString( path ) );
			if( 0 == shader )
			{
				logERROR( "couldn't create '{0}' from '{1}'", glbinding::aux::Meta::getString( type ), path );

				// TODO do the same as with the program object? -> store and use the dummy shader from here on, so future compiles don't need to be made if we know it will fail
				return( 0 );
			}
			else
			{
				m_shaders[ path ] = shader;
				return( shader );
			}
		}
	}
}

bool CShaderManager::InterfaceSetup( const std::shared_ptr< CShaderProgram > &shaderProgram ) const
{
	/*
	 * active attributes
	 */
	GLint numActiveAttributes = 0;
	glGetProgramInterfaceiv( shaderProgram->OpenGLID(), GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttributes );
	const std::array< GLenum, 3 > attributeProperties { { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint attribIndex = 0; attribIndex < numActiveAttributes; ++attribIndex )
	{
		GLint values[ attributeProperties.size() ];
		glGetProgramResourceiv( shaderProgram->OpenGLID(), GL_PROGRAM_INPUT, attribIndex, attributeProperties.size(), attributeProperties.data(), attributeProperties.size(), NULL, values );

		const GLint attributeLocation = values[ 2 ];

		const auto attributeIt = CShaderCompiler::AllowedAttributes.find( static_cast< CVAO::EAttributeLocation >( attributeLocation ) );
		if( std::end( CShaderCompiler::AllowedAttributes ) == attributeIt )
		{
			logERROR( "attribute location '{0}' is not allowed", attributeLocation );
			return( false );
		}
		else
		{
			std::vector< char > nameData( values[ 1 ] );
			glGetProgramResourceName( shaderProgram->OpenGLID(), GL_PROGRAM_INPUT, attribIndex, nameData.size(), nullptr, &nameData[ 0 ] );
			const std::string attributeName( nameData.data() );

			const GLenum attributeType = static_cast< GLenum>( values[ 0 ] );
			const SShaderInterface &attributeInterface = attributeIt->second;
			if( ( attributeInterface.name != attributeName )
				||
				( attributeInterface.type != attributeType ) )
			{
				logERROR( "attribute '{0}' with type {1} is not allowed at location '{2}'", attributeName, glbinding::aux::Meta::getString( attributeType ), attributeLocation );
				return( false );
			}
		}
	}

	/*
	 * active non-block uniforms
	 */
	GLint numActiveUniforms = 0;
	glGetProgramInterfaceiv( shaderProgram->OpenGLID(), GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms );
	const std::array< GLenum, 4 > uniformProperties { { GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint uniformIndex = 0; uniformIndex < numActiveUniforms; ++uniformIndex )
	{
		GLint values[ uniformProperties.size() ];
		glGetProgramResourceiv( shaderProgram->OpenGLID(), GL_UNIFORM, uniformIndex, uniformProperties.size(), uniformProperties.data(), uniformProperties.size(), nullptr, &values[ 0 ] );

		// skip any uniforms that are in a block.
		if( values[ 0 ] != -1 )
		{
			continue;
		}

		std::vector< char > nameData( values[ 2 ] );
		glGetProgramResourceName( shaderProgram->OpenGLID(), GL_UNIFORM, uniformIndex, nameData.size(), NULL, &nameData[ 0 ] );
		const std::string uniformName( nameData.data() );

		const GLint  uniformLocation = values[ 3 ];
		const GLenum uniformType = static_cast< GLenum>( values[ 1 ] );

		switch( uniformType )
		{
			case GL_SAMPLER_2D:
			case GL_SAMPLER_CUBE:
			case GL_SAMPLER_2D_ARRAY:
				shaderProgram->RequiredSamplers().emplace_back( std::make_pair( uniformLocation, SShaderInterface { uniformName, uniformType } ) );
				if( shaderProgram->RequiredSamplers().size() > CShaderManager::requiredCombinedTextureImageUnits )
				{
					logERROR( "uses {0} samplers but max {1} are allowed", shaderProgram->RequiredSamplers().size(), CShaderManager::requiredCombinedTextureImageUnits );
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
					const auto engineUniformIt = std::find_if(	std::cbegin( CShaderCompiler::EngineUniforms ),
																std::cend( CShaderCompiler::EngineUniforms ),
																[&]( const auto &uniform )
																{
																	return( uniform.second.name == uniformName );
																} );

					if( std::cend( CShaderCompiler::EngineUniforms ) != engineUniformIt )
					{
						// uniform gets provided by the engine

						const SShaderInterface &uniformInterface = engineUniformIt->second;
						if( uniformInterface.type != uniformType )
						{
							logERROR( "uniform '{0}' needs to be of type '{1}' but was declared as '{2}'", uniformName, glbinding::aux::Meta::getString( uniformInterface.type ), glbinding::aux::Meta::getString( uniformType ) );
							return( false );
						}
						else
						{
							shaderProgram->RequiredEngineUniforms().emplace_back( std::make_pair( uniformLocation, engineUniformIt->first ) );
						}
					}
					else
					{
						// uniform gets provided by the material

						shaderProgram->RequiredMaterialUniforms().emplace_back( std::make_pair( uniformLocation, SShaderInterface { uniformName, uniformType } ) );
					}
					break;
				}

			default:
				logERROR( "unsupported uniform type {0} for uniform '{1}'", glbinding::aux::Meta::getString( uniformType ), uniformName );
				return( false );
		}
	}

	return( true );
}
