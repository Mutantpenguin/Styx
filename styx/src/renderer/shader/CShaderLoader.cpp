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

void CShaderLoader::FromFile( const std::shared_ptr<CShader> &shader, const std::string &path ) const
{
	const std::string fileExtension = Path::Extension( path );
	
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "shader file '{0}' does not exist", path );
		
		if( fileExtension == std::string( "vert" ) )
		{
			FromVertexDummy( shader );
		}
		else if( fileExtension == std::string( "geom" ) )
		{
			FromGeometryDummy( shader );
		}
		else if( fileExtension == std::string( "frag" ) )
		{
			FromFragmentDummy( shader );
		}
	}
	else
	{
		const std::string body = m_filesystem.LoadFileToString( path );

		if( fileExtension == std::string( "vert" ) )
		{
			if( !m_shaderCompiler.Compile( shader, GL_VERTEX_SHADER, body ) )
			{
				logWARNING( "couldn't create vertex shader from '{0}'", path )
				FromVertexDummy( shader );
			}
		}
		else if( fileExtension == std::string( "geom" ) )
		{
			if( !m_shaderCompiler.Compile( shader, GL_GEOMETRY_SHADER, body ) )
			{
				logWARNING( "couldn't create geometry shader from '{0}'", path )
				FromGeometryDummy( shader );
			}
		}
		else if( fileExtension == std::string( "frag" ) )
		{
			if( !m_shaderCompiler.Compile( shader, GL_FRAGMENT_SHADER, body ) )
			{
				logWARNING( "couldn't create fragment shader from '{0}'", path )
				FromFragmentDummy( shader );
			}
		}
	}
}

void CShaderLoader::FromVertexDummy( const std::shared_ptr<CShader> &shader ) const
{
	shader->Reset();

	m_shaderCompiler.Compile( shader, GL_VERTEX_SHADER, CShaderCompiler::DummyVertexShaderBody );
}

void CShaderLoader::FromGeometryDummy( const std::shared_ptr<CShader> &shader ) const
{
	shader->Reset();

	m_shaderCompiler.Compile( shader, GL_GEOMETRY_SHADER, CShaderCompiler::DummyGeometryShaderBody );
}

void CShaderLoader::FromFragmentDummy( const std::shared_ptr<CShader> &shader ) const
{
	shader->Reset();

	m_shaderCompiler.Compile( shader, GL_FRAGMENT_SHADER, CShaderCompiler::DummyFragmentShaderBody );
}