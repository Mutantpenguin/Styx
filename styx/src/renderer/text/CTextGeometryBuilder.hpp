#pragma once

#include <string>
#include <memory>
#include <utility>

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
	using Lines = std::vector<std::pair<size_t, size_t>>;

	static void GenerateGeometry( const STextOptions &textOptions, const std::shared_ptr<const CFont> &font, const std::string &str, glm::vec2 &minBounds, glm::vec2 &maxBounds, Geometry<VertexPCU0> &geometry, Lines &lines );
	static void AdjustAlignment( const STextOptions &textOptions, const f16 maxLineWidth, std::vector<TextVertexFormat> &vertices, const Lines &lines );
	static void AdjustAnchoring( const STextOptions &textOptions, const glm::vec2 &minBounds, const glm::vec2 &maxBounds, std::vector<TextVertexFormat> &vertices );
};