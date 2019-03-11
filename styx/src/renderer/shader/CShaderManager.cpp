#include "CShaderManager.hpp"

#include <algorithm>

#include <glbinding-aux/Meta.h>

#include "src/logger/CLogger.hpp"

constexpr const GLint CShaderManager::requiredCombinedTextureImageUnits;

CShaderManager::CShaderManager( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler, CResourceCacheManager &resourceCacheManager ) :
	m_filesystem { p_filesystem },
	m_shaderCompiler { shaderCompiler },
	m_resourceCacheManager { resourceCacheManager }
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
}

bool CShaderManager::CreateDummyProgram()
{
	const auto &positionAttribute = CShaderCompiler::AllowedAttributes.at( CVAO::EAttributeLocation::position );
	const auto &uniformModelViewProjectionMatrix = CShaderCompiler::EngineUniforms.at( EEngineUniform::modelViewProjectionMatrix );
	// TODO remove
	const std::string vertexShaderString =	"void main()" \
											"{" \
											"	gl_Position = " + uniformModelViewProjectionMatrix.name + " * vec4( " + positionAttribute.name + ", 1 );" \
											"}";

	const auto vertexShader = std::make_shared<CShader>();
	if( !m_shaderCompiler.Compile( vertexShader, GL_VERTEX_SHADER, vertexShaderString ) )
	{
		logERROR( "couldn't create dummy vertex shader" );
		return( false );
	}
	// TODO remove
	const std::string fragmentShaderString = 	"out vec4 color;" \
												"void main()" \
												"{" \
												"	color = vec4( 1, 0, 1, 1 ).rgba;" \
												"}";

	const auto fragmentShader = std::make_shared<CShader>();
	if( !m_shaderCompiler.Compile( fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderString ) )
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

	m_dummyProgram = std::make_shared<CShaderProgram>( program );

	if( !InterfaceSetup( m_dummyProgram ) )
	{
		logWARNING( "dummy program object is not valid" );
		return( false );
	}

	return( true );
}

const std::shared_ptr<const CShaderProgram> CShaderManager::GetDummyShader() const
{
	return( m_dummyProgram );
}

const std::shared_ptr<const CShaderProgram> CShaderManager::LoadProgram( const CShaderProgram::ResourceIdType &paths )
{
	const std::string programIdentifier = paths.vertexShader + "|" + paths.fragmentShader;

	const auto it = m_programs.find( programIdentifier );
	if( std::end( m_programs ) != it )
	{
		return( it->second );
	}
	else
	{
		const auto vertexShader = m_resourceCacheManager.Get<CShader>( paths.vertexShader );
		if( nullptr == vertexShader )
		{
			logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", paths.vertexShader, paths.fragmentShader );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		const auto fragmentShader = m_resourceCacheManager.Get<CShader>( paths.fragmentShader );
		if( nullptr == fragmentShader )
		{
			logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", paths.vertexShader, paths.fragmentShader );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		const GLuint program = CreateProgram( vertexShader, fragmentShader );
		if( 0 == program )
		{
			logWARNING( "program object from vertex shader '{0}' and fragment shader '{1}' is not valid", paths.vertexShader, paths.fragmentShader );
			logWARNING( "using dummy shader" );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		auto shaderProgram = std::make_shared<CShaderProgram>( program );

		if( !InterfaceSetup( shaderProgram ) )
		{
			logWARNING( "unable to setup the interface for the program object from vertex shader '{0}' and fragment shader '{1}'", paths.vertexShader, paths.fragmentShader );
			logWARNING( "using dummy shader" );
			m_programs[ programIdentifier ] = m_dummyProgram;
			return( m_dummyProgram );
		}

		m_programs[ programIdentifier ] = shaderProgram;

		return( shaderProgram );
	}
}

const std::shared_ptr<const CShaderProgram> CShaderManager::CreateProgramFromShaders( const std::shared_ptr<const CShader> &vertexShader, const std::shared_ptr<const CShader> &fragmentShader ) const
{
	const GLuint program = CreateProgram( vertexShader, fragmentShader );
	if( 0 == program )
	{
		logWARNING( "program object is not valid" );
		logWARNING( "using dummy shader" );
		return( m_dummyProgram );
	}

	auto shaderProgram = std::make_shared<CShaderProgram>( program );

	if( !InterfaceSetup( shaderProgram ) )
	{
		logWARNING( "unable to setup the interface" );
		logWARNING( "using dummy shader" );
		return( m_dummyProgram );
	}

	return( shaderProgram );
}

GLuint CShaderManager::CreateProgram( const std::shared_ptr<const CShader> &vertexShader, const std::shared_ptr<const CShader> &fragmentShader ) const
{
	const GLuint program = glCreateProgram();
	if( 0 == program )
	{
		logWARNING( "Error creating program object" );
		return( 0 );
	}

	glAttachShader( program, vertexShader->GLID );
	glAttachShader( program, fragmentShader->GLID );

	glLinkProgram( program );

	GLint compileResult;
	glGetProgramiv( program, GL_LINK_STATUS, &compileResult );

	if( compileResult != static_cast<GLint>( GL_TRUE ) )
	{
		int infoLogLength;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> errorMessage( infoLogLength );
		glGetProgramInfoLog( program, infoLogLength, nullptr, errorMessage.data() );

		logWARNING( "Error linking program: {0}", errorMessage.data() );

		glDeleteProgram( program );

		return( 0 );
	}

	return( program );
}

bool CShaderManager::InterfaceSetup( const std::shared_ptr<CShaderProgram> &shaderProgram ) const
{
	/*
	 * active attributes
	 */
	GLint numActiveAttributes = 0;
	glGetProgramInterfaceiv( shaderProgram->OpenGLID(), GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttributes );
	const std::array<GLenum, 3> attributeProperties { { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint attribIndex = 0; attribIndex < numActiveAttributes; ++attribIndex )
	{
		GLint values[ attributeProperties.size() ];
		glGetProgramResourceiv( shaderProgram->OpenGLID(), GL_PROGRAM_INPUT, attribIndex, attributeProperties.size(), attributeProperties.data(), attributeProperties.size(), NULL, values );

		const GLint attributeLocation = values[ 2 ];

		const auto attributeIt = CShaderCompiler::AllowedAttributes.find( static_cast<CVAO::EAttributeLocation>( attributeLocation ) );
		if( std::end( CShaderCompiler::AllowedAttributes ) == attributeIt )
		{
			logERROR( "attribute location '{0}' is not allowed", attributeLocation );
			return( false );
		}
		else
		{
			std::vector<char> nameData( values[ 1 ] );
			glGetProgramResourceName( shaderProgram->OpenGLID(), GL_PROGRAM_INPUT, attribIndex, nameData.size(), nullptr, &nameData[ 0 ] );
			const std::string attributeName( nameData.data() );

			const GLenum attributeType = static_cast<GLenum>( values[ 0 ] );
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
	static const std::array<GLenum, 4> uniformProperties { { GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint uniformIndex = 0; uniformIndex < numActiveUniforms; ++uniformIndex )
	{
		GLint values[ uniformProperties.size() ];
		glGetProgramResourceiv( shaderProgram->OpenGLID(), GL_UNIFORM, uniformIndex, uniformProperties.size(), uniformProperties.data(), uniformProperties.size(), nullptr, &values[ 0 ] );

		// skip any uniforms that are in a block.
		if( values[ 0 ] != -1 )
		{
			continue;
		}

		std::vector<char> nameData( values[ 2 ] );
		glGetProgramResourceName( shaderProgram->OpenGLID(), GL_UNIFORM, uniformIndex, nameData.size(), NULL, &nameData[ 0 ] );
		const std::string uniformName( nameData.data() );

		const GLint  uniformLocation = values[ 3 ];
		const GLenum uniformType = static_cast<GLenum>( values[ 1 ] );

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
