#pragma once

#include <string>
#include <memory>

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

#include "src/renderer/font/CFont.hpp"

#include "STextOptions.hpp"

class CTextGeometryBuilder final
{
public:
	using TextVertexFormat = VertexPCU0;
	using TextGeometry = Geometry<TextVertexFormat>;

	static TextGeometry Build( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str );

private:
	static void AdjustAnchoring( const STextOptions &textOptions, const glm::vec2 minBounds, const glm::vec2 maxBounds, std::vector<TextVertexFormat> &vertices );
};