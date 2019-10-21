#include "CImage.hpp"

#include "src/core/Types.hpp"

#include "src/system/CFileSystem.hpp"

#include "src/helper/CColor.hpp"

namespace ImageHandler
{
	[[nodiscard]] std::shared_ptr<CImage> Load( const CFileSystem &p_filesystem, const fs::path &path, const u32 maxSize, const bool flipVertically );

	bool Save( const CFileSystem &p_filesystem, const std::shared_ptr<const CImage> &image, const std::string &format, const fs::path &path );

	[[nodiscard]] std::shared_ptr<CImage> GenerateCheckerImage( const CSize &size, const CColor &color1, const CColor &color2 );
}
