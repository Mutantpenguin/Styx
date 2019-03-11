#pragma once

#include <memory>

#include "src/renderer/shader/CShader.hpp"
#include "src/renderer/shader/CShaderProgram.hpp"

class CShaderProgramCompiler final
{
public:
	bool Compile( const std::shared_ptr<CShaderProgram> &shaderProgram, const std::shared_ptr<const CShader> &vertexShader, const std::shared_ptr<const CShader> &fragmentShader ) const;

	constexpr static const GLint RequiredCombinedTextureImageUnits { 16 };

private:
	[[ nodiscard ]] bool SetupInterface( const std::shared_ptr<CShaderProgram> &shaderProgram ) const;
};