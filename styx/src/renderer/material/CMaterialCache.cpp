#include "CMaterialCache.hpp"

#include "src/logger/CLogger.hpp"

CMaterialCache::CMaterialCache( const CFileSystem &filesystem, CShaderManager &shaderManager ) :
	CResourceCache( "material", filesystem ),
	m_materialLoader( filesystem, shaderManager )
{
}

