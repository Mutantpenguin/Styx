#include "CShaderProgramCompiler.hpp"

#include <glbinding-aux/Meta.h>

#include "src/logger/CLogger.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"

#include "src/core/StyxException.hpp"

constexpr const GLint CShaderProgramCompiler::RequiredCombinedTextureImageUnits;

CShaderProgramCompiler::CShaderProgramCompiler( const CShaderCompiler &shaderCompiler )
{
	m_dummyShaderProgram->VertexShader = shaderCompiler.DummyVertexShader();
	m_dummyShaderProgram->FragmentShader = shaderCompiler.DummyFragmentShader();
	
	if( !Compile( m_dummyShaderProgram ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create dummy shader program" );
	}
}

bool CShaderProgramCompiler::Compile( const std::shared_ptr<CShaderProgram> &shaderProgram ) const
{
	if( nullptr == shaderProgram->VertexShader )
	{
		logWARNING( "vertex shader not set" );
		return( false );
	}

	if( nullptr == shaderProgram->FragmentShader )
	{
		logWARNING( "fragment shader not set" );
		return( false );
	}

	shaderProgram->GLID = glCreateProgram();
	if( 0 == shaderProgram->GLID )
	{
		logWARNING( "Error creating program object" );
		return( false );
	}

	glAttachShader( shaderProgram->GLID, shaderProgram->VertexShader->GLID );

	if( nullptr != shaderProgram->GeometryShader )
	{
		glAttachShader( shaderProgram->GLID, shaderProgram->GeometryShader->GLID );
	}

	glAttachShader( shaderProgram->GLID, shaderProgram->FragmentShader->GLID );

	glLinkProgram( shaderProgram->GLID );

	GLint compileResult;
	glGetProgramiv( shaderProgram->GLID, GL_LINK_STATUS, &compileResult );

	if( compileResult != static_cast<GLint>( GL_TRUE ) )
	{
		int infoLogLength;
		glGetProgramiv( shaderProgram->GLID, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> errorMessage( infoLogLength );
		glGetProgramInfoLog( shaderProgram->GLID, infoLogLength, nullptr, errorMessage.data() );

		if( 0 < infoLogLength )
		{
			logWARNING( "Error linking program: {0}", errorMessage.data() );
		}
		else
		{
			logWARNING( "Error linking program: unknown reason" );
		}

		shaderProgram->Reset();

		return( false );
	}

	if( !SetupInterface( shaderProgram ) )
	{
		logWARNING( "unable to setup the interface" );

		shaderProgram->Reset();
		
		return( false );
	}

	return( true );
}

bool CShaderProgramCompiler::SetupInterface( const std::shared_ptr<CShaderProgram> &shaderProgram ) const
{
	/*
	 * active attributes
	 */
	GLint numActiveAttributes = 0;
	glGetProgramInterfaceiv( shaderProgram->GLID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttributes );
	const std::array<GLenum, 3> attributeProperties{ { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint attribIndex = 0; attribIndex < numActiveAttributes; ++attribIndex )
	{
		GLint values[ attributeProperties.size() ];
		glGetProgramResourceiv( shaderProgram->GLID, GL_PROGRAM_INPUT, attribIndex, attributeProperties.size(), attributeProperties.data(), attributeProperties.size(), NULL, values );

		const GLint attributeLocation = values[ 2 ];

		const auto attributeIt = CShaderCompiler::AllowedAttributes.find( static_cast<AttributeLocation>( attributeLocation ) );
		if( std::end( CShaderCompiler::AllowedAttributes ) == attributeIt )
		{
			logERROR( "attribute location '{0}' is not allowed", attributeLocation );
			return( false );
		}
		else
		{
			std::vector<char> nameData( values[ 1 ] );
			glGetProgramResourceName( shaderProgram->GLID, GL_PROGRAM_INPUT, attribIndex, nameData.size(), nullptr, &nameData[ 0 ] );
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
	glGetProgramInterfaceiv( shaderProgram->GLID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms );
	static const std::array<GLenum, 4> uniformProperties{ { GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION } };

	for( GLint uniformIndex = 0; uniformIndex < numActiveUniforms; ++uniformIndex )
	{
		GLint values[ uniformProperties.size() ];
		glGetProgramResourceiv( shaderProgram->GLID, GL_UNIFORM, uniformIndex, uniformProperties.size(), uniformProperties.data(), uniformProperties.size(), nullptr, &values[ 0 ] );

		// skip any uniforms that are in a block.
		if( values[ 0 ] != -1 )
		{
			continue;
		}

		std::vector<char> nameData( values[ 2 ] );
		glGetProgramResourceName( shaderProgram->GLID, GL_UNIFORM, uniformIndex, nameData.size(), NULL, &nameData[ 0 ] );
		const std::string uniformName( nameData.data() );

		const GLint  uniformLocation = values[ 3 ];
		const GLenum uniformType = static_cast<GLenum>( values[ 1 ] );

		switch( uniformType )
		{
		case GL_SAMPLER_2D:
		case GL_SAMPLER_CUBE:
		case GL_SAMPLER_2D_ARRAY:
			shaderProgram->AddRequiredSampler( uniformLocation, SShaderInterface{ uniformName, uniformType } );
			if( shaderProgram->RequiredSamplers().size() > CShaderProgramCompiler::RequiredCombinedTextureImageUnits )
			{
				logERROR( "uses {0} samplers but max {1} are allowed", shaderProgram->RequiredSamplers().size(), CShaderProgramCompiler::RequiredCombinedTextureImageUnits );
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
			const auto engineUniformIt = std::find_if( std::cbegin( CShaderCompiler::EngineUniforms ),
				std::cend( CShaderCompiler::EngineUniforms ),
				[ & ]( const auto &uniform )
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
					shaderProgram->AddRequiredEngineUniform( uniformLocation, engineUniformIt->first );
				}
			}
			else
			{
				// uniform gets provided by the material

				shaderProgram->AddRequiredMaterialUniform( uniformLocation, SShaderInterface{ uniformName, uniformType } );
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

const std::shared_ptr<const CShaderProgram> CShaderProgramCompiler::DummyShaderProgram() const
{
	return( m_dummyShaderProgram );
}