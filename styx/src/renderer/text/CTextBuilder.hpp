#pragma once

#include <memory>

#include "external/fmt/format.h"

#include "src/renderer/sampler/CSamplerManager.hpp"

#include "src/renderer/model/CMesh.hpp"
#include "src/renderer/font/CFont.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgramCompiler.hpp"

#include "CText.hpp"
#include "STextOptions.hpp"

class CTextBuilder final
{
public:
	CTextBuilder( const CSamplerManager &samplerManager, const CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler );
	
	template<typename... Args>
	std::shared_ptr<CText> Create( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str, const Args &... args ) const
	{
		return( Create( font, textOptions, fmt::format( str, args... ) ) );
	}

	std::shared_ptr<CText> Create( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str ) const;

private:
	const CSamplerManager &m_samplerManager;
	
	const std::shared_ptr<CMaterial> m_textMaterial;
	
	static const std::string m_fontTextureName;
	
	static const std::string FontVertexShaderBody;
	static const std::string FontFragmentShaderBody;
	
	static const CColor DefaultColor;
};
