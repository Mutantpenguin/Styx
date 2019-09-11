#include "CTextMeshBuilder.hpp"

#include "src/core/StyxException.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/geometry/Vertex.hpp"

const std::string CTextMeshBuilder::m_fontTextureName = "fontTexture";
const CColor CTextMeshBuilder::DefaultColor = { 0.0f, 0.0f, 0.0f };

const std::string CTextMeshBuilder::FontVertexShaderBody = R"glsl(
out vec3 vertexColor;
out vec2 UV;

void main()
{{
	gl_Position = {0} * vec4( {1}, 1 );
	
	vertexColor = {2};
	UV = {3};
}}
)glsl";

const std::string CTextMeshBuilder::FontFragmentShaderBody = R"glsl(
uniform sampler2D {0};

in vec3 vertexColor;
in vec2 UV;

out vec4 color;

void main()
{{
	color = vec4( vertexColor, texture( {0}, UV ).r );
}}
)glsl";

CTextMeshBuilder::CTextMeshBuilder( const CSamplerManager &samplerManager, const CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler ) :
	m_samplerManager { samplerManager },
	m_textMaterial { std::make_shared<CMaterial>() }
{
	if( !shaderCompiler.Compile( m_fontVertexShader, GL_VERTEX_SHADER, fmt::format( FontVertexShaderBody, CShaderCompiler::EngineUniforms.at( EEngineUniform::modelViewProjectionMatrix ).name, CShaderCompiler::AllowedAttributes.at( AttributeLocation::position ).name, CShaderCompiler::AllowedAttributes.at( AttributeLocation::color ).name, CShaderCompiler::AllowedAttributes.at( AttributeLocation::uv0 ).name ) ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create font vertex shader" );
	}

	if( !shaderCompiler.Compile( m_fontFragmentShader, GL_FRAGMENT_SHADER, fmt::format( FontFragmentShaderBody, m_fontTextureName ) ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create font fragment shader" );
	}
	
	m_fontShaderProgram->VertexShader = m_fontVertexShader;
	m_fontShaderProgram->FragmentShader = m_fontFragmentShader;
	
	if( !shaderProgramCompiler.Compile( m_fontShaderProgram ) )
	{
		THROW_STYX_EXCEPTION( "couldn't create font shader program" );
	}
	
	m_textMaterial->Name( "text render material" );
	m_textMaterial->EnableBlending( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	m_textMaterial->ShaderProgram( m_fontShaderProgram );
}

const std::shared_ptr<CMesh> CTextMeshBuilder::Create( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str ) const
{
	const auto color = textOptions.Color;
	const glm::vec3 standardColor( color.r(), color.g(), color.b() );

	Geometry<VertexPCU0> geometry;
	
	geometry.Mode = GL_TRIANGLES;
	
	auto &vertices = geometry.Vertices;
	auto &indices = geometry.Indices;
	
	// we need max this many vertices/indices, fewer if styling is used
	vertices.reserve( str.length() * 4 );
	indices.reserve( str.length() * 6 );
	
	u16 lastIndex = 0; // TODO rename
	
	glm::vec3 currentVertexColor = standardColor;
	EFontStyle currentStyle = EFontStyle::REGULAR;

	f16 offsetX = 0;
	f16 offsetY = 0;

	for( u16 i = 0; i < str.length(); i++ )
	{
		const auto &currentChar = str.at( i );

		switch( currentChar )
		{
		case '\n':
			offsetX = 0;
			offsetY += font->Size + textOptions.LineSpacing;
			continue;

		case '<':
			if( str.substr( i, 2 ) == "<#" ) // start of color
			{
				const auto &hexColorStr = str.substr( i + 2, 6 );
				const auto hexColorValue = std::stol( hexColorStr, nullptr, 16 );

				currentVertexColor.r = ( ( hexColorValue >> 16 ) & 0xFF ) / 255.0; // Extract the RR byte
				currentVertexColor.g = ( ( hexColorValue >> 8 ) & 0xFF ) / 255.0;  // Extract the GG byte
				currentVertexColor.b = ( ( hexColorValue ) & 0xFF ) / 255.0;       // Extract the BB byte

				i += 8;
				continue;
			}
			else if( str.substr( i, 4 ) == "</#>" ) // end of color
			{
				currentVertexColor = standardColor;

				i += 3;
				continue;
			}
			else if( str.substr( i, 3 ) == "<b>" ) // start of bold
			{
				currentStyle = EFontStyle::BOLD;

				i += 2;
				continue;
			}
			else if( str.substr( i, 4 ) == "</b>" ) // end of bold
			{
				currentStyle = EFontStyle::REGULAR;

				i += 3;
				continue;
			}

		default:
			const auto packedChar = font->PackedCharFromCodepoint( currentStyle, currentChar );

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
			}
			else
			{
				logWARNING( "codepoint '{0}' wasn't found in font '{1}' for style '{2}'", currentChar, font->Name, EFontStyleToString( currentStyle ) );
			}

			break;
		}
	}

	const CMesh::TMeshTextureSlots textureSlots = {	{ m_fontTextureName, std::make_shared<CMeshTextureSlot>( font->Texture, m_samplerManager.GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };	

	return( std::make_shared<CMesh>( geometry, m_textMaterial, textureSlots ) );
}