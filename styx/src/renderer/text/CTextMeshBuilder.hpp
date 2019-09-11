#pragma once

#include <memory>

#include "src/renderer/sampler/CSamplerManager.hpp"

#include "src/renderer/model/CMesh.hpp"
#include "src/renderer/font/CFont.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgramCompiler.hpp"

#include "src/helper/CColor.hpp"

class CTextMeshBuilder final
{
public:
	CTextMeshBuilder( const CSamplerManager &samplerManager, const CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler );
	
	template<typename... Args>
	const std::shared_ptr<CMesh> Create( const std::shared_ptr<const CFont> &font, const std::string &str, const Args &... args ) const
	{
		return( Create( font, DefaultColor, fmt::format( str, args... ) ) );
	}

	template<typename... Args>
	const std::shared_ptr<CMesh> Create( const std::shared_ptr<const CFont> &font, const CColor &color, const std::string &str, const Args &... args ) const
	{
		return( Create( font, color, fmt::format( str, args... ) ) );
	}

	const std::shared_ptr<CMesh> Create( const std::shared_ptr<const CFont> &font, const CColor &color, const std::string &str ) const;

private:
	const CSamplerManager &m_samplerManager;
	
	const std::shared_ptr<CMaterial> m_textMaterial;
	
	static const std::string m_fontTextureName;
	
	static const std::string FontVertexShaderBody;
	static const std::string FontFragmentShaderBody;
	
	const std::shared_ptr<CShader> m_fontVertexShader = std::make_shared<CShader>();
	const std::shared_ptr<CShader> m_fontFragmentShader = std::make_shared<CShader>();
	
	const std::shared_ptr<CShaderProgram> m_fontShaderProgram = std::make_shared<CShaderProgram>();
	
	static const CColor DefaultColor;
};
