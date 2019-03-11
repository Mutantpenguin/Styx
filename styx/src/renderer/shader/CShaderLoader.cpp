#include "CShaderLoader.hpp"

#include "src/logger/CLogger.hpp"

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
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "shader file '{0}' does not exist", path );
		FromDummy( shader );
	}
	else
	{
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

void CShaderLoader::FromDummy( const std::shared_ptr< CShader > &shader ) const
{
	shader->Reset();
}