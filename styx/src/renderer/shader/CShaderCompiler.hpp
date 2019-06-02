#pragma once

#include <memory>
#include <unordered_set>
#include <map>

#include "src/renderer/CUniformBuffer.hpp"
#include "src/renderer/CVertexArrayObject.hpp"

#include "src/renderer/shader/CShader.hpp"
#include "src/renderer/shader/EEngineUniform.hpp"
#include "src/renderer/shader/SShaderInterface.hpp"

#include "src/renderer/AttributeLocation.hpp"

class CShaderCompiler final
{
public:
	CShaderCompiler();

	bool Compile( const std::shared_ptr<CShader> &shader, const GLenum type, const std::string &body ) const;

	void RegisterUniformBuffer( const std::shared_ptr<const CUniformBuffer> &ubo );

	static const std::map<const AttributeLocation, const SShaderInterface> AllowedAttributes;

	static const std::unordered_map<EEngineUniform, const SShaderInterface> EngineUniforms;

	static const std::string DummyVertexShaderBody;
	static const std::string DummyGeometryShaderBody;
	static const std::string DummyFragmentShaderBody;

	const std::shared_ptr<const CShader> DummyVertexShader() const;
	const std::shared_ptr<const CShader> DummyGeometryShader() const;
	const std::shared_ptr<const CShader> DummyFragmentShader() const;

private:
	static const std::string srcAdditionShaderVersion;
	
	std::unordered_set<std::shared_ptr<const CUniformBuffer>> m_registeredUniformBuffers;

	const std::shared_ptr<CShader> m_dummyVertexShader = std::make_shared<CShader>();
	const std::shared_ptr<CShader> m_dummyGeometryShader = std::make_shared<CShader>();
	const std::shared_ptr<CShader> m_dummyFragmentShader = std::make_shared<CShader>();
};