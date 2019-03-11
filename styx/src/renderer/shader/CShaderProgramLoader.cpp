#include "CShaderProgramLoader.hpp"

#include "src/logger/CLogger.hpp"

CShaderProgramLoader::CShaderProgramLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
	logINFO( "shader program loader was initialized" );
}

CShaderProgramLoader::~CShaderProgramLoader()
{
	logINFO( "shader program loader is shutting down" );
}


void CShaderProgramLoader::FromFile( const std::shared_ptr<CShaderProgram> &shaderProgram, const CShaderProgram::ResourceIdType &id ) const
{
	// TODO
}