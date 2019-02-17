#pragma once

#include <array>
#include <memory>

#include "src/helper/Types.hpp"

#include "src/helper/image/CImage.hpp"

class CCubemapData final
{
public:
	static const u8 countCubemapFaces = 6;

	bool AddFace( const u8 faceNum, const std::shared_ptr< const CImage > &image );

	const std::array< std::shared_ptr< const CImage >, countCubemapFaces > &getFaces() const;

	bool isComplete() const;

private:
	std::array< std::shared_ptr< const CImage >, countCubemapFaces > m_faces;
};
