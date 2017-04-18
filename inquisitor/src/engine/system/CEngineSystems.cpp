#include "CEngineSystems.hpp"

CEngineSystems::CEngineSystems( const CSettings &settings, const CFileSystem &filesystem ) :
	Input( settings, filesystem ),
	Renderer( settings, filesystem ),
	SoundManager( settings, filesystem )
{
}

CEngineSystems::~CEngineSystems()
{
}

