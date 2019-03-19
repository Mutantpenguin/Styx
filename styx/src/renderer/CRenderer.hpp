#pragma once

#include <vector>

#include "src/helper/Types.hpp"

#include "src/system/CTimer.hpp"

#include "src/renderer/model/CMesh.hpp"

#include "src/system/CSettings.hpp"

#include "src/resource/CResourceCacheManager.hpp"

#include "src/scene/CScene.hpp"

#include "src/renderer/COpenGlAdapter.hpp"

#include "src/renderer/CFrameBuffer.hpp"

#include "src/renderer/texture/CTextureCache.hpp"
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
	CRenderer( const CSettings &settings, const CFileSystem &filesystem, CResourceCacheManager &resourceCacheManager );
	~CRenderer();

	CRenderer( const CRenderer &rhs ) = delete;
	CRenderer& operator = ( const CRenderer &rhs ) = delete;

public:
	CSamplerManager &SamplerManager();

	COpenGlAdapter &OpenGlAdapter();

	void	RenderSceneToFramebuffer( const CScene &scene, const CFrameBuffer &framebuffer, const CTimer &timer ) const;

	void	DisplayFramebuffer( const CFrameBuffer &framebuffer );

	class Exception: public std::exception
	{
	public:
		explicit Exception() {}

		virtual ~Exception() throw() {}
	};

private:
	struct MeshInstance
	{
		MeshInstance( const CMesh * p_mesh, const CTransform &p_transform, f16 p_viewDepth ) :
			mesh { p_mesh },
			Transform { p_transform },
			viewDepth { p_viewDepth }
		{}

		const CMesh * mesh;
		CTransform Transform;
		f16 viewDepth;
	};

	using TRenderBucket	= std::vector< MeshInstance >;

	const CSettings &m_settings;

	CResourceCacheManager &m_resourceCacheManager;

	COpenGlAdapter m_OpenGlAdapter;

	CShaderCompiler			m_shaderCompiler;
	CShaderProgramCompiler	m_shaderProgramCompiler;

	CSamplerManager		m_samplerManager;

	std::shared_ptr< CTextureCache >		m_textureCache;
	std::shared_ptr< CMaterialCache >		m_materialCache;
	std::shared_ptr< CShaderCache >			m_shaderCache;
	std::shared_ptr< CShaderProgramCache >	m_shaderProgramCache;

	void CreateUniformBuffers();
	void UpdateUniformBuffers( const std::shared_ptr< const CEntity > &cameraEntity, const CTimer &timer ) const;

	void RenderBucket( const TRenderBucket &bucketMaterials, const glm::mat4 &viewMatrix, const glm::mat4 &viewProjectionMatrix ) const;

	[[nodiscard]] glm::mat4 CalculateModelMatrix( const CTransform &transform ) const;

	std::shared_ptr< CUniformBuffer > m_uboCamera;
	std::shared_ptr< CUniformBuffer > m_uboTimer;
	std::shared_ptr< CUniformBuffer > m_uboScreen;

	std::unique_ptr< CMesh >	m_meshFrameBuffer;
	const std::string m_slotNameFrameBuffer = "screenTexture";
};
