#include "CShaderProgramCache.hpp"



CShaderProgramCache::CShaderProgramCache( const CFileSystem &p_filesystem ) :
	CResourceCache( "shaderprogram", p_filesystem )
{
}