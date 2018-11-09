#include "CImage.hpp"

#include "src/engine/helper/Types.hpp"

#include "src/engine/system/CFileSystem.hpp"

namespace ImageHandler
{
	[[nodiscard]] std::shared_ptr< CImage > Load( const CFileSystem &p_filesystem, const std::string &path, const u32 maxSize, const u8 picMip, const bool flipVertically );

	bool Save( const CFileSystem &p_filesystem, const std::shared_ptr< const CImage > &image, const f16 scale_factor, const std::string &format, const std::string &path );

	[[nodiscard]] std::shared_ptr< CImage > GenerateCheckerImage( const CSize &size );
}
