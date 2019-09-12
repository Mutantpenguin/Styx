#include "CTextGeometryBuilder.hpp"

#include "external/utfcpp/utf8.h"

#include "src/logger/CLogger.hpp"

CTextGeometryBuilder::TextGeometry CTextGeometryBuilder::Build( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str )
{
	if( !utf8::is_valid( str ) )
	{
		logWARNING( "string '{0}' contains invalid unicode codepoints" );
		utf8::replace_invalid( str );
	}

	const auto color = textOptions.Color;
	const glm::vec3 standardColor( color.r(), color.g(), color.b() );

	TextGeometry geometry;

	geometry.Mode = GL_TRIANGLES;

	auto &vertices = geometry.Vertices;
	auto &indices = geometry.Indices;

	// we need max this many vertices/indices, fewer if styling is used
	vertices.reserve( str.length() * 4 );
	indices.reserve( str.length() * 6 );

	u16 lastIndex = 0; // TODO rename

	glm::vec3 currentVertexColor = standardColor;
	EFontWeight currentWeight = EFontWeight::REGULAR;

	// for the anchoring
	glm::vec2 minBounds;
	glm::vec2 maxBounds;

	f16 offsetX = 0;
	f16 offsetY = 0;

	auto it = str.begin();
	const auto end = str.end();

	while( it != end )
	{
		const u32 &currentCodepoint = utf8::next( it, end );

		switch( currentCodepoint )
		{
		case '\n':
			offsetX = 0;
			offsetY += font->Size + textOptions.LineSpacing;
			continue;

		case '<':
		{
			const std::string remainder( it, end );

			if( remainder.substr( 0, 1 ) == "#" ) // start of color
			{
				const auto &hexColorStr = remainder.substr( 2, 6 );
				const auto hexColorValue = std::stol( hexColorStr, nullptr, 16 );

				currentVertexColor.r = ( ( hexColorValue >> 16 ) & 0xFF ) / 255.0; // Extract the RR byte
				currentVertexColor.g = ( ( hexColorValue >> 8 ) & 0xFF ) / 255.0;  // Extract the GG byte
				currentVertexColor.b = ( ( hexColorValue ) & 0xFF ) / 255.0;       // Extract the BB byte

				utf8::advance( it, 8, end );
				continue;
			}
			else if( remainder.substr( 0, 3 ) == "/#>" ) // end of color
			{
				currentVertexColor = standardColor;

				utf8::advance( it, 3, end );
				continue;
			}
			else if( remainder.substr( 0, 2 ) == "b>" ) // start of bold
			{
				currentWeight = EFontWeight::BOLD;

				utf8::advance( it, 2, end );
				continue;
			}
			else if( remainder.substr( 0, 3 ) == "/b>" ) // end of bold
			{
				currentWeight = EFontWeight::REGULAR;

				utf8::advance( it, 3, end );
				continue;
			}
		}

		default:
			const auto packedChar = font->PackedCharFromCodepoint( currentWeight, currentCodepoint );

			if( nullptr != packedChar )
			{
				stbtt_aligned_quad quad;

				stbtt_GetPackedQuad( packedChar, font->AtlasSize.width, font->AtlasSize.height, 0, &offsetX, &offsetY, &quad, 1 );

				vertices.emplace_back( VertexPCU0( { { quad.x0, -quad.y1, 0 }, currentVertexColor, { quad.s0, quad.t1 } } ) );
				vertices.emplace_back( VertexPCU0( { { quad.x0, -quad.y0, 0 }, currentVertexColor, { quad.s0, quad.t0 } } ) );
				vertices.emplace_back( VertexPCU0( { { quad.x1, -quad.y0, 0 }, currentVertexColor, { quad.s1, quad.t0 } } ) );
				vertices.emplace_back( VertexPCU0( { { quad.x1, -quad.y1, 0 }, currentVertexColor, { quad.s1, quad.t1 } } ) );

				indices.emplace_back( lastIndex );
				indices.emplace_back( lastIndex + 1 );
				indices.emplace_back( lastIndex + 2 );

				indices.emplace_back( lastIndex );
				indices.emplace_back( lastIndex + 2 );
				indices.emplace_back( lastIndex + 3 );

				lastIndex += 4;

				minBounds.x = std::min( { minBounds.x, quad.x0, quad.x1 } );
				minBounds.y = std::min( { minBounds.y, -quad.y0, -quad.y1 } );
				maxBounds.x = std::max( { maxBounds.x, quad.x0, quad.x1 } );
				maxBounds.y = std::max( { maxBounds.y, -quad.y0, -quad.y1 } );
			}
			else
			{
				logWARNING( "codepoint '{0}' wasn't found in font '{1}' for weight '{2}'", currentCodepoint, font->Name, EFontWeightToString( currentWeight ) );
			}

			break;
		}
	}

	AdjustAnchoring( textOptions, minBounds, maxBounds, vertices );

	return( geometry );
}

void CTextGeometryBuilder::AdjustAnchoring( const STextOptions &textOptions, const glm::vec2 minBounds, const glm::vec2 maxBounds, std::vector<TextVertexFormat> &vertices )
{
	f16 xShift = 0.0f;
	f16 yShift = 0.0f;

	switch( textOptions.HorizontalAnchoring )
	{
	case EAnchoringHorizontal::LEFT:
		xShift = minBounds.x;
		break;

	case EAnchoringHorizontal::CENTER:
		xShift = ( minBounds.x + maxBounds.x ) / 2.0f;
		break;

	case EAnchoringHorizontal::RIGHT:
		xShift = maxBounds.x;
		break;
	}

	switch( textOptions.VerticalAnchoring )
	{
	case EAnchoringVertical::TOP:
		yShift = minBounds.y;
		break;

	case EAnchoringVertical::CENTER:
		yShift = ( minBounds.y + maxBounds.y ) / 2.0f;
		break;

	case EAnchoringVertical::BOTTOM:
		yShift = maxBounds.y;
		break;
	}

	if( ( xShift != 0.0f )
		||
		( yShift != 0.0f ) )
	{
		for( auto &vertex : vertices )
		{
			vertex.Position.x -= xShift;
			vertex.Position.y -= yShift;
		}
	}
}