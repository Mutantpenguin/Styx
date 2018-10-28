#pragma once

#include <vector>

#include "src/engine/system/CTimer.hpp"

#include "src/engine/renderer/model/CMesh.hpp"

#include "src/engine/system/CSettings.hpp"

#include "src/engine/resource/CResourceCacheManager.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"

#include "src/engine/renderer/CFrameBuffer.hpp"

#include "src/engine/renderer/texture/CTextureCache.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"
#include "src/engine/renderer/material/CMaterialCache.hpp"

#include "src/engine/helper/CColor.hpp"

class CRenderer final
{
friend class CEngine;
friend class CEngineInterface;

private:
	CRenderer( const CSettings &settings, const CFileSystem &filesystem, CResourceCacheManager &resourceCacheManager );
	~CRenderer( void );

	CRenderer( const CRenderer &rhs ) = delete;
	CRenderer& operator = ( const CRenderer &rhs ) = delete;

public:
	CSamplerManager		&SamplerManager( void );

	COpenGlAdapter	&OpenGlAdapter( void );

	void	RenderSceneToFramebuffer( const CScene &scene, const CFrameBuffer &framebuffer, const CTimer &timer ) const;

	void	DisplayFramebuffer( const CFrameBuffer &framebuffer );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	struct MeshInstance
	{
		MeshInstance( const CMesh * p_mesh, const CTransform &p_transform, float p_viewDepth ) :
			mesh { p_mesh },
			Transform { p_transform },
			viewDepth { p_viewDepth }
		{}

		const CMesh * mesh;
		CTransform Transform;
		float viewDepth;
	};

	using TRenderBucket	= std::vector< MeshInstance >;

	const	CSettings &m_settings;

	CResourceCacheManager &m_resourceCacheManager;

	COpenGlAdapter m_OpenGlAdapter;

	CSamplerManager		m_samplerManager;
	CShaderManager		m_shaderManager;

	std::shared_ptr< CTextureCache >	m_textureCache;
	std::shared_ptr< CMaterialCache >	m_materialCache;

	void CreateUniformBuffers( void );
	void UpdateUniformBuffers( const std::shared_ptr< const CEntity > &cameraEntity, const CTimer &timer ) const;

	void RenderBucket( const TRenderBucket &bucketMaterials, const glm::mat4 &viewProjectionMatrix ) const;

	[[nodiscard]] glm::mat4 CalculateModelMatrix( const CTransform &transform ) const;

	std::shared_ptr< CUniformBuffer > m_uboCamera;
	std::shared_ptr< CUniformBuffer > m_uboTimer;
	std::shared_ptr< CUniformBuffer > m_uboScreen;

	std::unique_ptr< CMesh >	m_meshFrameBuffer;
	const std::string m_slotNameFrameBuffer = "screenTexture";
};
