#include "CEngineInterface.hpp"

CEngineInterface::CEngineInterface( const CSettings &settings, const CFileSystem &filesystem ) :
	Input( settings, filesystem ),
	Renderer( settings, filesystem, ResourceCacheManager ),
	Audio( settings, filesystem, ResourceCacheManager )
{
}
