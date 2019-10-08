#include "CState.hpp"

#include "external/minitrace/minitrace.h"

#include "src/renderer/components/CModelComponent.hpp"

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

	RenderPackage renderPackage;

	const auto &cameraEntity = m_scene.Camera();

	if( !cameraEntity )
	{
		logWARNING( "scene has no camera" );
	}
	else
	{
		/*
		 * set up the render package
		 */

		renderPackage.ClearColor = m_scene.ClearColor();
		renderPackage.TimeMilliseconds = static_cast<glm::uint>( m_timer.Time() / 1000 );

		auto &renderLayer = renderPackage.m_renderLayers.emplace_back();

		const auto &camera = cameraEntity->Get<CCameraComponent>();

		auto &view = renderLayer.View;

		view.Position = cameraEntity->Transform.Position;
		view.Direction = cameraEntity->Transform.Direction();
		view.ProjectionMatrix = camera->ProjectionMatrix();
		view.ViewMatrix = camera->ViewMatrix();
		view.ViewProjectionMatrix = camera->ViewProjectionMatrix();

		// TODO is this the right amount?
		renderLayer.drawCommands.reserve( 10000 );

		MTR_BEGIN( "GFX", "fill draw drawCommands" );
		const auto &cameraFrustum = cameraEntity->Get<CCameraComponent>()->Frustum();

		const auto &cameraPosition = cameraEntity->Transform.Position;

		m_scene.Each<CModelComponent>( [ &cameraFrustum, &cameraPosition, &renderLayer ]( const std::shared_ptr<const CEntity> &entity )
		{
			const auto &mesh = entity->Get<CModelComponent>()->Mesh().get();

			const auto &transform = entity->Transform;

			// TODO use Octree here
			if( cameraFrustum.IsSphereInside( transform.Position, glm::length( mesh->BoundingSphereRadiusVector * transform.Scale ) ) )
			{
				const CMaterial * material = mesh->Material().get();

				renderLayer.drawCommands.emplace_back( mesh, material, material->ShaderProgram().get(), transform.ModelMatrix(), glm::length2( transform.Position - cameraPosition ) );
			}
		} );
		MTR_END( "GFX", "fill draw drawCommands" );

		MTR_BEGIN( "GFX", "sort" );
		renderPackage.SortDrawCommands();
		MTR_END( "GFX", "sort" );
	}

	return( renderPackage );
}