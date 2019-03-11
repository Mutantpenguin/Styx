#pragma once

#include <memory>
#include <unordered_set>
#include <map>

#include "src/renderer/CUniformBuffer.hpp"
#include "src/renderer/CVAO.hpp"

#include "src/renderer/shader/CShader.hpp"
#include "src/renderer/shader/EEngineUniform.hpp"
#include "src/renderer/shader/SShaderInterface.hpp"

class CShaderCompiler final
{
public:
	[[ nodiscard ]] bool Compile( const std::shared_ptr<CShader> &shader, const GLenum type, const std::string &body ) const;

	void RegisterUniformBuffer( const std::shared_ptr< const CUniformBuffer > &ubo );

	static const std::map< const CVAO::EAttributeLocation, const SShaderInterface > AllowedAttributes;

	static const std::unordered_map< EEngineUniform, const SShaderInterface > EngineUniforms;

private:
	static const std::string srcAdditionShaderVersion;
	
	std::unordered_set< std::shared_ptr< const CUniformBuffer > > m_registeredUniformBuffers;
};