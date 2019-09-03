#include "CTextBuilder.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/geometry/Vertex.hpp"

const CText CTextBuilder::Create( const std::string &str, const std::shared_ptr<CFont> &font ) const
{
	CText text;
	
	text.Value = str;
	
	text.Geometry.Mode = GL_TRIANGLES;
	
	u16 lastIndex = 0; // TODO rename
	f16 offsetX = 0;
	f16 offsetY = 0;
	for( const auto &c : str )
	{
		const auto index = font->IndexFromCodepoint( c );
		
		if( index != std::numeric_limits<u32>::max() )
		{
			stbtt_aligned_quad quad;
			
			stbtt_GetPackedQuad( font->PackedChars.get(), font->AtlasSize.width, font->AtlasSize.height, index, &offsetX, &offsetY, &quad, 1 );
			
			auto &vertices = text.Geometry.Vertices;
			auto &indices = text.Geometry.Indices;
			
			vertices.emplace_back( VertexPCU0( { { quad.x0, -quad.y1, 0 }, {}, { quad.s0, quad.t1 } } ) );
			vertices.emplace_back( VertexPCU0( { { quad.x0, -quad.y0, 0 }, {}, { quad.s0, quad.t0 } } ) );
			vertices.emplace_back( VertexPCU0( { { quad.x1, -quad.y0, 0 }, {}, { quad.s1, quad.t0 } } ) );
			vertices.emplace_back( VertexPCU0( { { quad.x1, -quad.y1, 0 }, {}, { quad.s1, quad.t1 } } ) );
			
			indices.emplace_back( lastIndex );
			indices.emplace_back( lastIndex + 1 );
			indices.emplace_back( lastIndex + 2 );
			
			indices.emplace_back( lastIndex );
			indices.emplace_back( lastIndex + 2 );
			indices.emplace_back( lastIndex + 3 );
			
			lastIndex += 4;
		}
		else
		{
			logWARNING( "codepoint '{0}' wasn't found in font '{1}'", c, font->Name ); // TODO last parameter
		}
	}
	
	return( text );
}