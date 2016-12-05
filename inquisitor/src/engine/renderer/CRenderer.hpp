#ifndef CRENDERER_HPP
#define CRENDERER_HPP

#include <list>

#include "src/engine/renderer/camera/CCamera.hpp"

#include "src/engine/renderer/CMesh.hpp"

#include "src/engine/system/CSettings.hpp"

#include "src/engine/scene/CScene.hpp"

#include "src/engine/renderer/material/CMaterialManager.hpp"
#include "src/engine/renderer/sampler/CSamplerManager.hpp"

#include "src/engine/helper/CColor.hpp"
#include "src/engine/helper/image/CImage.hpp"

class CRenderer final
{
public:
	CRenderer( const CSettings &settings, const CFileSystem &filesystem );

	void	Update( const float delta );

	std::shared_ptr< CImage > GetScreenshot( void ) const;

	std::shared_ptr< CMaterial > LoadMaterial( const std::string &path );

	void	SetClearColor( const CColor &color );

	void	Clear( bool colorBuffer, bool depthBuffer ) const;

	void	RenderScene( const CScene &scene, const std::uint64_t time ) const;

private:
	typedef std::vector< std::shared_ptr< const CMesh > > TRenderQueue;

	const	CSettings &m_settings;

	CSamplerManager		m_samplerManager;
	CMaterialManager	m_materialmanager;

	CRendererCapabilities m_rendererCapabilities;

	void CreateUniformBuffers( void );
	void UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const std::uint64_t time ) const;

	void RenderMesh( const std::shared_ptr< const CCamera > &camera, const std::shared_ptr< const CMesh > &mesh ) const;

	GLint m_maxCombinedTextureImageUnits { 0 };

	std::shared_ptr< CUniformBuffer > m_uboCamera;
	std::shared_ptr< CUniformBuffer > m_uboTimer;
};

#endif // CRENDERER_HPP
