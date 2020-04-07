#include "CState.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "external/minitrace/minitrace.h"

#include "src/renderer/components/CModelComponent.hpp"
#include "src/renderer/components/CGuiModelComponent.hpp"

CState::CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface ) :
		m_name { name },
		m_frameBuffer( settings.renderer.window.size ),
		m_filesystem { filesystem },
		m_settings { settings },
		m_engineInterface { engineInterface }
{}

std::shared_ptr<CState> CState::Update()
{
	switch( m_status )
	{
		case eStatus::RUNNING:
			return( OnUpdate() );

		case eStatus::PAUSED:
			return( shared_from_this() );

		default:
			throw std::runtime_error( fmt::format( "unknown status '{0}' for state '{1}'", static_cast<u8>( m_status ), m_name ) );
	};
}

void CState::Pause()
{
	if( eStatus::RUNNING == m_status )
	{
		OnPause();

		m_timer.Pause();

		m_status = eStatus::PAUSED;
	};
}

void CState::Resume()
{
	if( eStatus::PAUSED == m_status )
	{
		OnResume();

		m_timer.Resume();

		m_status = eStatus::RUNNING;
	};
}

const std::string &CState::Name() const
{
	return( m_name );
}

const CFrameBuffer &CState::FrameBuffer() const
{
	return( m_frameBuffer );
}

RenderPackage CState::CreateRenderPackage() const
{
	MTR_SCOPE( "GFX", "RenderSceneToFramebuffer" );

	/*
	 * set up the render package
	 */

	RenderPackage renderPackage;

	renderPackage.ClearColor = m_scene.ClearColor();
	renderPackage.TimeMilliseconds = static_cast<glm::uint>( m_timer.Time() / 1000 );

	const auto &cameraEntity = m_scene.Camera();

	if( cameraEntity )
	{
		/*
		 * set up the render layer for the camera
		 */

		auto &renderLayer = renderPackage.RenderLayers.emplace_back();

		const auto &camera = cameraEntity->Get<CCameraComponent>();

		auto &view = renderLayer.View;

		view.Position = cameraEntity->Transform.Position;
		view.Direction = cameraEntity->Transform.Direction();
		view.ProjectionMatrix = camera->ProjectionMatrix();
		view.ViewMatrix = camera->ViewMatrix();
		view.ViewProjectionMatrix = camera->ViewProjectionMatrix();

		// TODO is this the right amount?
		renderLayer.drawCommands.reserve( 10000 );

		MTR_BEGIN( "GFX", "fill draw drawCommands for camera" );
		
		const auto &cameraFrustum = camera->Frustum();

		const auto &cameraPosition = cameraEntity->Transform.Position;

		m_scene.Each<CModelComponent>( [ &cameraFrustum, &cameraPosition, &renderLayer ]( const std::shared_ptr<const CEntity> &entity )
		{
			const auto &mesh = entity->Get<CModelComponent>()->Mesh.get();

			const auto &transform = entity->Transform;

			// TODO use Octree here
			if( cameraFrustum.IsSphereInside( transform.Position, glm::length( mesh->BoundingSphereRadiusVector * transform.Scale ) ) )
			{
				const CMaterial * material = mesh->Material().get();

				renderLayer.drawCommands.emplace_back( material->Blending(), mesh, material, material->ShaderProgram().get(), transform.ModelMatrix(), glm::length2( transform.Position - cameraPosition ) );
			}
		} );
		
		MTR_END( "GFX", "fill draw drawCommands for camera" );
	}

	/*
	 * set up the render layer for the GUI
	 */

	{
		auto &renderLayer = renderPackage.RenderLayers.emplace_back();

		auto &view = renderLayer.View;

		const auto windowSize = m_settings.renderer.window.size;

		view.Position = { 0.0f, 0.0f, 0.0f };
		view.Direction = { 0.0f, 0.0f, 1.0f };
		view.ProjectionMatrix = glm::ortho( 0.0f, static_cast<f16>( windowSize.width ), 0.0f, static_cast<f16>( windowSize.height ), 0.0f, 1000.0f );
		view.ViewMatrix = glm::mat4( 1.0f );
		view.ViewProjectionMatrix = view.ProjectionMatrix * view.ViewMatrix;

		// TODO is this the right amount?
		renderLayer.drawCommands.reserve( 1000 );

		m_scene.Each<CGuiModelComponent>( [&renderLayer]( const std::shared_ptr<const CEntity> &entity )
		{
			const auto &guiMesh = entity->Get<CGuiModelComponent>()->Mesh.get();

			const auto &transform = entity->Transform;

			const CMaterial * material = guiMesh->Material().get();

			renderLayer.drawCommands.emplace_back( material->Blending(), guiMesh, material, material->ShaderProgram().get(), transform.ModelMatrix(), glm::length2( transform.Position ) );
		} );
	}

	MTR_BEGIN( "GFX", "sort" );
	renderPackage.SortDrawCommands();
	MTR_END( "GFX", "sort" );

	return( renderPackage );
}