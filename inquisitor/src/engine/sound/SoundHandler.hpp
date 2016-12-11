#include "CSound.hpp"

#include "src/engine/system/CFileSystem.hpp"

namespace SoundHandler
{
	std::shared_ptr< CSound > Load( const CFileSystem &p_filesystem, const std::string &path );
}
