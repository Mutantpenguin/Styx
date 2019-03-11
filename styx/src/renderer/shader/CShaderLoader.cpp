#include "CShaderLoader.hpp"

#include "src/logger/CLogger.hpp"

#include "src/helper/Path.hpp"

CShaderLoader::CShaderLoader( const CFileSystem &p_filesystem, const CShaderCompiler &shaderCompiler ) :
		m_filesystem { p_filesystem },
		m_shaderCompiler { shaderCompiler }
{
	logINFO( "shader loader was initialized" );
}

CShaderLoader::~CShaderLoader()
{
	logINFO( "shader loader is shutting down" );
}

void CShaderLoader::FromFile( const std::shared_ptr< CShader > &shader, const std::string &path ) const
{
	const std::string fileExtension = Path::Extension( path );
	
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "shader file '{0}' does not exist", path );
		
		if( fileExtension == std::string( "vs.glsl" ) )
		{
			FromVertexDummy( shader );
		}
		else if( fileExtension == std::string( "fs.glsl" ) )
		{
			FromFragmentDummy( shader );
		}
	}
	else
	{
		const std::string body = m_filesystem.LoadFileToString( path );

		if( fileExtension == std::string( "vs.glsl" ) )
		{
			if( !m_shaderCompiler.Compile( shader, GL_VERTEX_SHADER, body ) )
			{
				FromVertexDummy( shader );
			}
		}
		else if( fileExtension == std::string( "fs.glsl" ) )
		{
			if( !m_shaderCompiler.Compile( shader, GL_FRAGMENT_SHADER, body ) )
			{
				FromFragmentDummy( shader );
			}
		}

		// TODO logERROR( "couldn't create '{0}' from '{1}'", glbinding::aux::Meta::getString( type ), path );

		/* TODO
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
		*/
	}
}

void CShaderLoader::FromVertexDummy( const std::shared_ptr< CShader > &shader ) const
{
	shader->Reset();

	// TODO
	const auto &positionAttribute = CShaderCompiler::AllowedAttributes.at( CVAO::EAttributeLocation::position );
	const auto &uniformModelViewProjectionMatrix = CShaderCompiler::EngineUniforms.at( EEngineUniform::modelViewProjectionMatrix );

	const std::string vertexShaderString =	"void main()" \
											"{" \
											"	gl_Position = " + uniformModelViewProjectionMatrix.name + " * vec4( " + positionAttribute.name + ", 1 );" \
											"}";

	if( !m_shaderCompiler.Compile( shader, GL_VERTEX_SHADER, vertexShaderString ) )
	{
		// TODO log it
	}
}

void CShaderLoader::FromFragmentDummy( const std::shared_ptr< CShader > &shader ) const
{
	shader->Reset();

	// TODO
	const std::string fragmentShaderString =	"out vec4 color;" \
												"void main()" \
												"{" \
												"	color = vec4( 1, 0, 1, 1 ).rgba;" \
												"}";

	if( !m_shaderCompiler.Compile( shader, GL_FRAGMENT_SHADER, fragmentShaderString ) )
	{
		// TODO log it
	}
}