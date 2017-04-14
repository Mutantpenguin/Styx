#ifndef CRENDERER_HPP
#define CRENDERER_HPP

#include <list>

#include "src/engine/renderer/camera/CCamera.hpp"

#include "src/engine/renderer/CMesh.hpp"

#include "src/engine/system/CSettings.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/renderer/COpenGlAdapter.hpp"
#include "src/engine/renderer/material/CMaterialManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

#include "src/engine/helper/CColor.hpp"
#include "src/engine/helper/image/CImage.hpp"

class CRenderer final
{
public:
	CRenderer( const CSettings &settings, const CFileSystem &filesystem );

	void	Update( void );

	std::shared_ptr< CImage > GetScreenshot( void ) const;

	void ReloadResources( void );

	std::shared_ptr< CMaterial > LoadMaterial( const std::string &path );

	void	SetClearColor( const CColor &color );

	void	Clear( bool colorBuffer, bool depthBuffer ) const;

	void	RenderScene( const CScene &scene, const std::uint64_t time ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	using TRenderQueueMeshes = std::vector< const CMesh * >;
	using TRenderQueueMaterials = std::unordered_map< const CMaterial *, TRenderQueueMeshes >;

	const	CSettings &m_settings;

	COpenGlAdapter m_OpenGlAdapter;

	CSamplerManager		m_samplerManager;
	CMaterialManager	m_materialManager;

	void CreateUniformBuffers( void );
	void UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const std::uint64_t time ) const;

	void SetupMaterial( const CMaterial * const material ) const;

	void RenderQueueMeshes( const TRenderQueueMeshes &queueMeshes, const glm::mat4 &viewProjectionMatrix ) const;
	void RenderQueueMaterials( const TRenderQueueMaterials &queueMaterials, const glm::mat4 &viewProjectionMatrix ) const;
	void RenderMesh( const CMesh * const mesh, const glm::mat4 &viewProjectionMatrix, const CShaderProgram * const shader ) const;

	std::shared_ptr< CUniformBuffer > m_uboCamera;
	std::shared_ptr< CUniformBuffer > m_uboTimer;
};

#endif // CRENDERER_HPP
