#pragma once

#include <array>
#include <memory>

#include "src/helper/Types.hpp"

#include "src/helper/image/CImage.hpp"

class CCubemapData final
{
public:
	static const u8 cubemapFaceCount = 6;

	bool SetFace( const u8 faceNum, const std::shared_ptr< const CImage > &image );

	const std::array< std::shared_ptr< const CImage >, cubemapFaceCount > &getFaces() const;

	bool isComplete() const;

private:
	std::array< std::shared_ptr< const CImage >, cubemapFaceCount > m_faces;
};
