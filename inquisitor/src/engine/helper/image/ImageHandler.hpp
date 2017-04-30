#include "CImage.hpp"

#include <cstdint>

#include "src/engine/system/CFileSystem.hpp"

namespace ImageHandler
{
	[[nodiscard]] std::shared_ptr< CImage > Load( const CFileSystem &p_filesystem, const std::string &path, const std::uint32_t maxSize, const std::uint8_t picMip, const bool flipVertically );

	bool Save( const CFileSystem &p_filesystem, const std::shared_ptr< const CImage > &image, const float scale_factor, const std::string &format, const std::string &path );

	std::shared_ptr< CImage > GenerateCheckerImage( const CSize &size );
}
