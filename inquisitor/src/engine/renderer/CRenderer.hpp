#ifndef CRENDERER_HPP
#define CRENDERER_HPP

#include <list>

#include "src/engine/system/CTimer.hpp"

#include "src/engine/scene/camera/CCamera.hpp"

#include "src/engine/renderer/model/CMesh.hpp"

#include "src/engine/system/CSettings.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"

#include "src/engine/renderer/CFrameBuffer.hpp"

#include "src/engine/renderer/texture/CTextureManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"
#include "src/engine/renderer/material/CMaterialManager.hpp"

#include "src/engine/helper/CColor.hpp"

class CRenderer final
{
friend class CEngine;
friend class CEngineInterface;

private:
	CRenderer( const CSettings &settings, const CFileSystem &filesystem );
	~CRenderer( void );


	CRenderer( const CRenderer &rhs ) = delete;
	CRenderer& operator = ( const CRenderer &rhs ) = delete;

	void	Update( void );

public:
	void ReloadResources( void );

	CMaterialManager	&MaterialManager( void );
	CTextureManager		&TextureManager( void );
	CSamplerManager		&SamplerManager( void );

	void	RenderSceneToFramebuffer( const CScene &scene, const CFrameBuffer &framebuffer, const CTimer &timer ) const;

	void	DisplayFramebuffer( const CFrameBuffer &framebuffer );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	using TRenderBucket	= std::vector< CScene::MeshInstance >;

	const	CSettings &m_settings;

	COpenGlAdapter m_OpenGlAdapter;

	CTextureManager		m_textureManager;
	CSamplerManager		m_samplerManager;
	CShaderManager		m_shaderManager;
	CMaterialManager	m_materialManager;

	void CreateUniformBuffers( void );
	void UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const CTimer &timer ) const;

	void RenderBucket( const TRenderBucket &bucketMaterials, const glm::mat4 &viewProjectionMatrix ) const;

	[[nodiscard]] glm::mat4 CalculateModelMatrix( const CTransformComponent &transform ) const;

	std::shared_ptr< CUniformBuffer > m_uboCamera;
	std::shared_ptr< CUniformBuffer > m_uboTimer;
	std::shared_ptr< CUniformBuffer > m_uboScreen;

	std::unique_ptr< CMesh >	m_meshFrameBuffer;
};

#endif // CRENDERER_HPP
