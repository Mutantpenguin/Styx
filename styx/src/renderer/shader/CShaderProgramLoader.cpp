#include "CShaderProgramLoader.hpp"

#include "external/json/json.hpp"
using json = nlohmann::json;

#include "src/logger/CLogger.hpp"

#include "src/core/FileExtension.hpp"

CShaderProgramLoader::CShaderProgramLoader( const CFileSystem &p_filesystem, CResources &resources, CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler ) :
	m_filesystem { p_filesystem },
	m_resources { resources },
	m_shaderCompiler { shaderCompiler },
	m_shaderProgramCompiler { shaderProgramCompiler }
{
	logINFO( "shader program loader was initialized" );
}

CShaderProgramLoader::~CShaderProgramLoader()
{
	logINFO( "shader program loader is shutting down" );
}

void CShaderProgramLoader::FromFile( const std::shared_ptr<CShaderProgram> &shaderProgram, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", path.generic_string() );
		FromDummy( shaderProgram );
		return;
	}

	const std::string fileExtensionString = path.extension().generic_string();
	
	if( fileExtensionString != FileExtension::ShaderProgram::shp )
	{
		logWARNING( "file type '{0}' of shader program file '{1}' is not supported", fileExtensionString, path.generic_string() );
		FromDummy( shaderProgram );
	}
	else if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "shader program file '{0}' does not exist", path.generic_string() );
		FromDummy( shaderProgram );
	}
	else
	{
		const std::string body = m_filesystem.LoadFileToString( path );

		if( fileExtensionString == std::string( ".shp" ) )
		{
			try
			{
				if( !FromShpFile( shaderProgram, path ) )
				{
					FromDummy( shaderProgram );
				}
			}
			catch( std::exception &e )
			{
				logWARNING( "error loading shader program '{0}': {1}", path.generic_string(), e.what() );
				FromDummy( shaderProgram );
			}
		}
	}
}

bool CShaderProgramLoader::FromShpFile( const std::shared_ptr<CShaderProgram> &shaderProgram, const fs::path &path ) const
{
	json shp_root;

	try
	{
		shp_root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path.generic_string(), e.what() );
		return( false );
	}
	
	const auto shader_vs = shp_root.find( "vs" );
	if( shader_vs == shp_root.end() )
	{
		logWARNING( "no vertex shader specified in '{0}'", path.generic_string() );
		return( false );
	}
	else
	{
		shaderProgram->VertexShader = m_resources.Get<CShader>( shader_vs->get<std::string>() );
	}

	const auto shader_gs = shp_root.find( "gs" );
	if( shader_gs != shp_root.end() )
	{
		shaderProgram->GeometryShader = m_resources.Get<CShader>( shader_gs->get<std::string>() );
	}

	const auto shader_fs = shp_root.find( "fs" );
	if( shader_fs == shp_root.end() )
	{
		logWARNING( "no fragment shader specified in '{0}'", path.generic_string() );
		return( false );
	}
	else
	{
		shaderProgram->FragmentShader = m_resources.Get<CShader>( shader_fs->get<std::string>() );
	}

	if( !m_shaderProgramCompiler.Compile( shaderProgram ) )
	{
		logWARNING( "program object from '{0}' is not valid", path.generic_string() );
		return( false );
	}
	
	return( true );
}

void CShaderProgramLoader::FromDummy( const std::shared_ptr<CShaderProgram> &shaderProgram ) const
{
	shaderProgram->Reset();
	
	shaderProgram->VertexShader = m_shaderCompiler.DummyVertexShader();
		
	shaderProgram->GeometryShader = nullptr;

	shaderProgram->FragmentShader = m_shaderCompiler.DummyFragmentShader();
	
	// TODO log if this fails?
	m_shaderProgramCompiler.Compile( shaderProgram );
}