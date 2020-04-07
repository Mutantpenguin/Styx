#pragma once

#include <vector>

#include "src/core/Types.hpp"

#include "src/renderer/model/CMesh.hpp"

#include "src/system/CSettings.hpp"

#include "src/resource/CResources.hpp"

#include "src/scene/CScene.hpp"

#include "src/renderer/COpenGlAdapter.hpp"

#include "src/renderer/CFrameBuffer.hpp"

#include "src/renderer/RenderPackage.hpp"

#include "src/renderer/texture/CTextureCache.hpp"
#include "src/renderer/model/CModelCache.hpp"
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
	COpenGlAdapter OpenGlAdapter;
	
	CShaderCompiler			ShaderCompiler;
	CShaderProgramCompiler	ShaderProgramCompiler;

	void RenderPackageToFramebuffer( const RenderPackage &renderPackage, const CFrameBuffer &framebuffer ) const;

	// presents the framebuffer on screen
	void DisplayFramebuffer( const CFrameBuffer &framebuffer );

private:
	const CSettings &m_settings;

	CResources &m_resources;

	std::shared_ptr<CTextureCache>			m_textureCache;
	std::shared_ptr<CModelCache>			m_modelCache;
	std::shared_ptr<CMaterialCache>			m_materialCache;
	std::shared_ptr<CShaderCache>			m_shaderCache;
	std::shared_ptr<CShaderProgramCache>	m_shaderProgramCache;

	void CreateUniformBuffers();
	void UpdateFramebufferUniformBuffers( const CFrameBuffer &framebuffer ) const;
	void UpdateRenderPackageUniformBuffers( const RenderPackage &renderPackage ) const;
	void UpdateRenderLayerUniformBuffers( const RenderLayer &renderLayer ) const;

	std::shared_ptr<CUniformBuffer> m_uboView;
	std::shared_ptr<CUniformBuffer> m_uboTimer;
	std::shared_ptr<CUniformBuffer> m_uboFramebuffer;
};
