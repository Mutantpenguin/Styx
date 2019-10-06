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

	static void AddCodepoint( f16 &offsetX, f16 &offsetY, const glm::vec3 &currentVertexColor, const EFontWeight currentWeight, const u32 &currentCodepoint, const std::shared_ptr<const CFont> &font, TextGeometry &textGeometry, u16 &lastIndex, glm::vec2 &minBounds, glm::vec2 &maxBounds );

	static void GenerateGeometry( const STextOptions &textOptions, const std::shared_ptr<const CFont> &font, const std::string &str, glm::vec2 &minBounds, glm::vec2 &maxBounds, TextGeometry &textGeometry, Lines &lines );
	static void AdjustAlignment( const STextOptions &textOptions, const f16 maxLineWidth, std::vector<TextVertexFormat> &vertices, const Lines &lines );
	static void AdjustAnchoring( const STextOptions &textOptions, const glm::vec2 &minBounds, const glm::vec2 &maxBounds, std::vector<TextVertexFormat> &vertices );
};