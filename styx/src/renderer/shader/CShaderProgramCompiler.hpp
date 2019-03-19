#pragma once

#include <memory>

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgram.hpp"

class CShaderProgramCompiler final
{
public:
	CShaderProgramCompiler( const CShaderCompiler &shaderCompiler );

	bool Compile( const std::shared_ptr<CShaderProgram> &shaderProgram ) const;

	constexpr static const GLint RequiredCombinedTextureImageUnits { 16 };

	const std::shared_ptr<const CShaderProgram> DummyShaderProgram() const;

private:
	[[ nodiscard ]] bool SetupInterface( const std::shared_ptr<CShaderProgram> &shaderProgram ) const;

	const std::shared_ptr<CShaderProgram> m_dummyShaderProgram = std::make_shared<CShaderProgram>();
};