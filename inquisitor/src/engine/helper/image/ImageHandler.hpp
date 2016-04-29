#include "CImage.hpp"

#include <cstdint>

#include "../../system/CFileSystem.hpp"

namespace ImageHandler
{
	std::shared_ptr< CImage > Load( const CFileSystem &p_filesystem, const std::string &path, const std::uint32_t maxSize, const unsigned int picMip, const bool flipVertically );

	bool Save( const CFileSystem &p_filesystem, const std::shared_ptr< const CImage > &image, const float scale_factor, const std::string &format, const std::string &path );

	std::shared_ptr< CImage > GenerateCheckerImage( const CSize &size );
}
