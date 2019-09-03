#include "CRenderer.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glbinding-aux/Meta.h>

#include "external/minitrace/minitrace.h"

#include "src/renderer/CGLState.hpp"

#include "src/renderer/components/CModelComponent.hpp"
#include "src/scene/components/camera/CCameraComponent.hpp"

#include "src/logger/CLogger.hpp"

#include "src/core/StyxException.hpp"

#include "src/renderer/geometry/prefabs/Quad.hpp"

CRenderer::CRenderer( const CSettings &settings, const CFileSystem &filesystem, CResources &resources ) :
	m_settings { settings },
	m_resources { resources },
	OpenGlAdapter( settings ),
	ShaderCompiler(),
	ShaderProgramCompiler( ShaderCompiler ),
	m_textureCache { std::make_shared<CTextureCache>( filesystem, OpenGlAdapter ) },
	m_modelCache { std::make_shared<CModelCache>( filesystem, resources ) },
	m_materialCache { std::make_shared<CMaterialCache>( filesystem, resources, ShaderProgramCompiler ) },
	m_shaderCache { std::make_shared<CShaderCache>( filesystem, ShaderCompiler ) },
	m_shaderProgramCache { std::make_shared<CShaderProgramCache>( filesystem, resources, ShaderCompiler, ShaderProgramCompiler ) }
{
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );

	glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );
	
	// start with a black window so it doesn't show garbage
	glClearColor( 0, 0, 0, 0 );		
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	CreateUniformBuffers();

	m_resources.AddCache<CTexture>( m_textureCache );
	m_resources.AddCache<CModel>( m_modelCache );
	m_resources.AddCache<CShader>( m_shaderCache );
	m_resources.AddCache<CShaderProgram>( m_shaderProgramCache );
	m_resources.AddCache<CMaterial>( m_materialCache );

	logINFO( "renderer was initialized" );
}

CRenderer::~CRenderer()
{
	logINFO( "renderer is shutting down" );

	m_resources.RemoveCache( m_materialCache );
	m_resources.RemoveCache( m_shaderProgramCache );
	m_resources.RemoveCache( m_shaderCache );
	m_resources.RemoveCache( m_modelCache );
	m_resources.RemoveCache( m_textureCache );
}

void CRenderer::CreateUniformBuffers()
{
	{
		const std::string cameraBody =	"vec3 position;" \
										"vec3 direction;" \
										"mat4 projectionMatrix;" \
										"mat4 viewMatrix;" \
										"mat4 viewProjectionMatrix;";

		// use glm::vec4 for position and direction, else we get rendering errors. seems to be a problem with some OpenGL implementations
		m_uboCamera = std::make_shared<CUniformBuffer>( ( 2 * sizeof( glm::vec4 ) ) + ( 3 * sizeof( glm::mat4 ) ), GL_DYNAMIC_DRAW, EUniformBufferLocation::CAMERA, "Camera", cameraBody );
		ShaderCompiler.RegisterUniformBuffer( m_uboCamera );
	}

	{
		const std::string timerBody = "uint time;";

		m_uboTimer = std::make_shared<CUniformBuffer>( sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, "Timer", timerBody );
		ShaderCompiler.RegisterUniformBuffer( m_uboTimer );
	}

	{
		const std::string framebufferBody = 	"uint width;" \
												"uint height;";

		m_uboFramebuffer = std::make_shared<CUniformBuffer>( 2 * sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::FRAMEBUFFER, "Framebuffer", framebufferBody );
		ShaderCompiler.RegisterUniformBuffer( m_uboFramebuffer );
	}
}

void CRenderer::UpdateFramebufferUniformBuffers( const CFrameBuffer &framebuffer ) const
{
	m_uboFramebuffer->SubData( 0,					sizeof( glm::uint ), &framebuffer.Size.width );
	m_uboFramebuffer->SubData( sizeof( glm::uint ),	sizeof( glm::uint ), &framebuffer.Size.height );
}

void CRenderer::UpdateRenderPackageUniformBuffers( const RenderPackage &renderPackage ) const
{
	/*
	 * Update time into the uniform buffer
	 */

	m_uboTimer->SubData( 0,	sizeof( glm::uint ), &renderPackage.TimeMilliseconds );
}

void CRenderer::UpdateRenderLayerUniformBuffers( const RenderLayer &renderLayer ) const
{
	/*
	 * Update calculated values into the uniform buffer
	 */
	
	auto const &view = renderLayer.View;

	u32 offset = 0;
	m_uboCamera->SubData( offset,	sizeof( view.Position ),				glm::value_ptr( view.Position ) );
	offset += sizeof( glm::vec4 );
	m_uboCamera->SubData( offset,	sizeof( view.Direction ),				glm::value_ptr( view.Direction ) );
	offset += sizeof( glm::vec4 );
	m_uboCamera->SubData( offset,	sizeof( view.ProjectionMatrix ),		glm::value_ptr( view.ProjectionMatrix ) );
	offset += sizeof( glm::mat4 );
	m_uboCamera->SubData( offset,	sizeof( view.ViewMatrix ),				glm::value_ptr( view.ViewMatrix ) );
	offset += sizeof( glm::mat4 );
	m_uboCamera->SubData( offset,	sizeof( view.ViewProjectionMatrix ),	glm::value_ptr( view.ViewProjectionMatrix ) );
}

void CRenderer::RenderSceneToFramebuffer( const CScene &scene, const CFrameBuffer &framebuffer, const CTimer &timer ) const
{
	MTR_SCOPE( "GFX", "RenderSceneToFramebuffer" );

	const auto &cameraEntity = scene.Camera();

	if( !cameraEntity )
	{
		logWARNING( "scene has no camera" );
	}
	else
	{
		/*
		 * set up the render package
		 */

		RenderPackage renderPackage;

		renderPackage.ClearColor = scene.ClearColor();
		renderPackage.TimeMilliseconds = static_cast<glm::uint>( timer.Time() / 1000 );
		
		auto &renderLayer = renderPackage.m_renderLayers.emplace_back();	
		
		const auto &camera = cameraEntity->Get<CCameraComponent>();

		auto &view = renderLayer.View;

		view.Position = cameraEntity->Transform.Position();
		view.Direction = cameraEntity->Transform.Direction();
		view.ProjectionMatrix = camera->ProjectionMatrix();
		view.ViewMatrix = camera->ViewMatrix();
		view.ViewProjectionMatrix = camera->ViewProjectionMatrix();
		
		// TODO is this the right amount?
		renderLayer.drawCommands.reserve( 10000 );

		MTR_BEGIN( "GFX", "fill draw drawCommands" );
		const auto &cameraFrustum = cameraEntity->Get<CCameraComponent>()->Frustum();

		const auto &cameraPosition = cameraEntity->Transform.Position();

		scene.Each<CModelComponent>( [ &cameraFrustum, &cameraPosition, &renderLayer ] ( const std::shared_ptr<const CEntity> &entity )
		{
			const auto &mesh = entity->Get<CModelComponent>()->Mesh().get();

			const auto &transform = entity->Transform;

			// TODO use Octree here
			if( cameraFrustum.IsSphereInside( transform.Position(), glm::length( mesh->BoundingSphereRadiusVector * transform.Scale() ) ) )
			{
				const CMaterial * material = mesh->Material().get();

				renderLayer.drawCommands.emplace_back( mesh, material, material->ShaderProgram().get(), transform.ModelMatrix(), glm::length2( transform.Position() - cameraPosition ) );
			}
		} );
		MTR_END( "GFX", "fill draw drawCommands" );

		MTR_BEGIN( "GFX", "sort" );
		renderPackage.SortDrawCommands();
		MTR_END( "GFX", "sort" );

		Render( framebuffer, renderPackage );
	}
}

void CRenderer::Render( const CFrameBuffer &framebuffer, const RenderPackage &renderPackage ) const
{
	MTR_SCOPE( "GFX", "Render" );

	framebuffer.Bind();
	
	framebuffer.Clear( renderPackage.ClearColor );
	
	UpdateFramebufferUniformBuffers( framebuffer );
	
	UpdateRenderPackageUniformBuffers( renderPackage );

	for( const auto &layer : renderPackage.m_renderLayers )
	{
		UpdateRenderLayerUniformBuffers( layer );
		
		auto &view = layer.View;
		
		const CMesh * currentMesh = nullptr;
		const CMaterial * currentMaterial = nullptr;
		const CShaderProgram * currentShader = nullptr;

		for( const auto & [ mesh, material, shaderProgram, modelMatrix, viewDepth ] : layer.drawCommands )
		{
			if( currentMesh != mesh )
			{
				currentMesh = mesh;

				if( currentMaterial != material )
				{
					currentMaterial = material;
					material->Activate();

					currentShader = shaderProgram;
				}

				mesh->Bind();
			}

			for( const auto & [ location, engineUniform ] : currentShader->RequiredEngineUniforms() )
			{
				switch( engineUniform )
				{
					case EEngineUniform::modelViewProjectionMatrix:
						glUniformMatrix4fv( location, 1, GL_FALSE, &( view.ViewProjectionMatrix * modelMatrix )[ 0 ][ 0 ] );
						break;

					case EEngineUniform::modelViewMatrix:
						glUniformMatrix4fv( location, 1, GL_FALSE, &( view.ViewMatrix * modelMatrix )[ 0 ][ 0 ] );
						break;

					case EEngineUniform::modelMatrix:
						glUniformMatrix4fv( location, 1, GL_FALSE, &modelMatrix[ 0 ][ 0 ] );
						break;
				}
			}

			mesh->Draw();
		}
	}

	framebuffer.Unbind();
}

void CRenderer::DisplayFramebuffer( const CFrameBuffer &framebuffer )
{
	// TODO if we remove this, we get problems with the depth buffer. why is that?
	CGLState::DepthMask( GL_TRUE );

	const auto &framebufferSize = framebuffer.Size;
	const auto &screenSize = m_settings.renderer.window.size;

	glBlitNamedFramebuffer(
		framebuffer.GLID, // src is framebuffer
		0, // dest is screen
		0, 0, framebufferSize.width, framebufferSize.height, // src bounds
		0, 0, screenSize.width, screenSize.height, // dest bounds
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
		GL_NEAREST
	);
}