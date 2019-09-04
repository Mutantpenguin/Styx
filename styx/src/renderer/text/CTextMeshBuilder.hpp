#pragma once

#include <memory>

#include "src/renderer/sampler/CSamplerManager.hpp"

#include "src/renderer/model/CMesh.hpp"
#include "src/renderer/font/CFont.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CTextMeshBuilder final
{
public:
	CTextMeshBuilder( const CSamplerManager &samplerManager, const CShaderCompiler &shaderCompiler, CShaderProgramCompiler &shaderProgramCompiler );
	
	const std::shared_ptr<CMesh> Create( const std::string &str, const std::shared_ptr<const CFont> &font ) const;

private:
	const CSamplerManager &m_samplerManager;
	
	const std::shared_ptr<CMaterial> m_textMaterial;
	
	static const std::string m_fontTextureName;
	
	static const std::string FontVertexShaderBody;
	static const std::string FontFragmentShaderBody;
	
	const std::shared_ptr<CShader> m_fontVertexShader = std::make_shared<CShader>();
	const std::shared_ptr<CShader> m_fontFragmentShader = std::make_shared<CShader>();
	
	const std::shared_ptr<CShaderProgram> m_fontShaderProgram = std::make_shared<CShaderProgram>();
	
	const glm::vec3 m_defaultColor { 0.0f, 0.0f, 0.0f };
};
