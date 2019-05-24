#pragma once

#include <vector>

#include "src/core/Types.hpp"

#include "src/system/CTimer.hpp"

#include "src/renderer/model/CMesh.hpp"

#include "src/system/CSettings.hpp"

#include "src/resource/CResources.hpp"

#include "src/scene/CScene.hpp"

#include "src/renderer/COpenGlAdapter.hpp"

#include "src/renderer/CFrameBuffer.hpp"

#include "src/renderer/DrawCommand.hpp"

#include "src/renderer/texture/CTextureCache.hpp"
#include "src/renderer/model/CModelCache.hpp"
#include "src/renderer/sampler/CSamplerManager.hpp"
#include "src/renderer/material/CMaterialCache.hpp"

#include "src/renderer/shader/CShaderCompiler.hpp"
#include "src/renderer/shader/CShaderProgramCompiler.hpp"

#include "src/renderer/shader/CShaderCache.hpp"
#include "src/renderer/shader/CShaderProgramCache.hpp"

#include "src/helper/CColor.hpp"

class CRenderer final
{
friend class CEngine;
friend class CEngineInterface;

private:
	CRenderer( const CSettings &settings, const CFileSystem &filesystem, CResources &resources );
	~CRenderer();

	CRenderer( const CRenderer &rhs ) = delete;
	CRenderer& operator = ( const CRenderer &rhs ) = delete;

public:
	CSamplerManager &SamplerManager();

	COpenGlAdapter &OpenGlAdapter();

	void RenderSceneToFramebuffer( const CScene &scene, const CFrameBuffer &framebuffer, const CTimer &timer ) const;

	// presents the framebuffer on screen
	void DisplayFramebuffer( const CFrameBuffer &framebuffer );

private:
	const CSettings &m_settings;

	CResources &m_resources;

	COpenGlAdapter m_OpenGlAdapter;

	CSamplerManager m_samplerManager;
	
	CShaderCompiler			m_shaderCompiler;
	CShaderProgramCompiler	m_shaderProgramCompiler;

	std::shared_ptr<CTextureCache>			m_textureCache;
	std::shared_ptr<CModelCache>			m_modelCache;
	std::shared_ptr<CMaterialCache>			m_materialCache;
	std::shared_ptr<CShaderCache>			m_shaderCache;
	std::shared_ptr<CShaderProgramCache>	m_shaderProgramCache;

	void CreateUniformBuffers();
	void UpdateUniformBuffers( const std::shared_ptr<const CEntity> &cameraEntity, const CTimer &timer ) const;

	void Render( const DrawCommandList &drawCommands, const glm::mat4 &viewMatrix, const glm::mat4 &viewProjectionMatrix ) const;

	std::shared_ptr<CUniformBuffer> m_uboCamera;
	std::shared_ptr<CUniformBuffer> m_uboTimer;
	std::shared_ptr<CUniformBuffer> m_uboScreen;
};
