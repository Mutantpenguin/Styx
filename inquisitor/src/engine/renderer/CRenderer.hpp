#ifndef CRENDERER_HPP
#define CRENDERER_HPP

#include <list>

#include "src/engine/system/CTimer.hpp"

#include "src/engine/renderer/camera/CCamera.hpp"

#include "src/engine/renderer/model/CMesh.hpp"

#include "src/engine/system/CSettings.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"

#include "src/engine/renderer/texture/CTextureManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"
#include "src/engine/renderer/material/CMaterialManager.hpp"

#include "src/engine/helper/CColor.hpp"
#include "src/engine/helper/image/CImage.hpp"

class CRenderer final
{
friend class CEngine;
friend class CEngineSystems;

private:
	CRenderer( const CSettings &settings, const CFileSystem &filesystem );
	CRenderer( const CRenderer &rhs ) = delete;
	CRenderer& operator = ( const CRenderer &rhs ) = delete;

	void	Update( void );

public:
	std::shared_ptr< CImage > GetScreenshot( void ) const;

	void ReloadResources( void );

	CMaterialManager	&MaterialManager( void );
	CTextureManager		&TextureManager( void );
	CSamplerManager		&SamplerManager( void );

	void	SetClearColor( const CColor &color ) const;

	void	Clear( bool colorBuffer, bool depthBuffer ) const;

	void	RenderScene( const CScene &scene, const CTimer &timer ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	// TODO order by mesh?
	using TRenderBucketMeshes		= std::vector< const CMesh * >;
	using TRenderBucketMaterials	= std::unordered_map< const CMaterial *, TRenderBucketMeshes >;

	const	CSettings &m_settings;

	COpenGlAdapter m_OpenGlAdapter;

	CTextureManager		m_textureManager;
	CSamplerManager		m_samplerManager;
	CMaterialManager	m_materialManager;

	void CreateUniformBuffers( void );
	void UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const CTimer &timer ) const;

	void SetupMaterial( const CMaterial * const material ) const;

	void RenderBucketMeshes( const TRenderBucketMeshes &bucketMeshes, const glm::mat4 &viewProjectionMatrix ) const;
	void RenderBucketMaterials( const TRenderBucketMaterials &bucketMaterials, const glm::mat4 &viewProjectionMatrix ) const;
	void RenderMesh( const CMesh * const mesh, const glm::mat4 &viewProjectionMatrix, const CShaderProgram * const shader ) const;

	std::shared_ptr< CUniformBuffer > m_uboCamera;
	std::shared_ptr< CUniformBuffer > m_uboTimer;
	std::shared_ptr< CUniformBuffer > m_uboScreen;
};

#endif // CRENDERER_HPP
