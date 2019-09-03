#include "CTextBuilder.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/geometry/Vertex.hpp"

const std::shared_ptr<CMesh> CTextMeshBuilder::Create( const std::string &str, const std::shared_ptr<CFont> &font ) const
{
	Geometry<VertexPCU0> geometry;
	
	geometry.Mode = GL_TRIANGLES;
	
	u16 lastIndex = 0; // TODO rename
	f16 offsetX = 0;
	f16 offsetY = 0;
	for( const auto &c : str )
	{
		const auto packedChar = font->PackedCharFromCodepoint( c );
		
		if( nullptr != packedChar )
		{
			stbtt_aligned_quad quad;
			
			stbtt_GetPackedQuad( packedChar, font->AtlasSize.width, font->AtlasSize.height, 0, &offsetX, &offsetY, &quad, 1 );
			
			auto &vertices = geometry.Vertices;
			auto &indices = geometry.Indices;
			
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
	
	const CMesh::TMeshTextureSlots textureSlots = {};
	return( std::make_shared<CMesh>( geometry, nullptr, textureSlots ) );
}