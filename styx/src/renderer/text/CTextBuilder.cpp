#include "CTextBuilder.hpp"

#include "src/core/StyxException.hpp"

#include "CTextGeometryBuilder.hpp"

const std::string CTextBuilder::m_fontTextureName = "fontTexture";
const CColor CTextBuilder::DefaultColor = { 0.0f, 0.0f, 0.0f };

const std::string CTextBuilder::FontVertexShaderBody = R"glsl(
out vec3 vertexColor;
out vec2 UV;

void main()
{{
	gl_Position = {0} * vec4( {1}, 1 );
	
	vertexColor = {2};
	UV = {3};
}}
)glsl";

const std::string CTextBuilder::FontFragmentShaderBody = R"glsl(
uniform sampler2D {0};

in vec3 vertexColor;
in vec2 UV;

out vec4 color;

void main()
{{
	color = vec4( vertexColor, texture( {0}, UV ).r );
}}
)glsl";

CTextBuilder::CTextBuilder( const CSamplerManager &samplerManager, const CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler ) :
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
	m_textMaterial->DisableDepthMask();
	m_textMaterial->ShaderProgram( m_fontShaderProgram );
}

std::shared_ptr<CText> CTextBuilder::Create( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str ) const
{
	const auto geometry = CTextGeometryBuilder::Build( font, textOptions, str );
	
	const CMesh::TMeshTextureSlots textureSlots = {	{ m_fontTextureName, std::make_shared<CMeshTextureSlot>( font->Texture, m_samplerManager.GetFromType( CSampler::SamplerType::EDGE_2D ) ) } };	

	const auto mesh = std::make_shared<CMesh>( geometry, m_textMaterial, textureSlots, true );

	return( std::make_shared<CText>( font, textOptions, str, mesh ) );
}
