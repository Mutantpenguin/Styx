#include "CRenderer.hpp"

#include <algorithm>

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
	m_samplerManager( settings ),
	m_shaderCompiler(),
	m_shaderProgramCompiler( m_shaderCompiler ),
	m_textureCache { std::make_shared<CTextureCache>( settings, filesystem, m_OpenGlAdapter ) },
	m_modelCache { std::make_shared<CModelCache>( filesystem, resources ) },
	m_materialCache { std::make_shared<CMaterialCache>( filesystem, resources, m_shaderProgramCompiler ) },
	m_shaderCache { std::make_shared<CShaderCache>( filesystem, m_shaderCompiler ) },
	m_shaderProgramCache { std::make_shared<CShaderProgramCache>( filesystem, resources, m_shaderCompiler, m_shaderProgramCompiler ) }
{
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );

	glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );

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
		m_shaderCompiler.RegisterUniformBuffer( m_uboCamera );
	}

	{
		const std::string timerBody = "uint time;";

		m_uboTimer = std::make_shared<CUniformBuffer>( sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, "Timer", timerBody );
		m_shaderCompiler.RegisterUniformBuffer( m_uboTimer );
	}

	{
		const std::string screenBody = 	"uint width;" \
										"uint height;";

		m_uboScreen = std::make_shared<CUniformBuffer>( 2 * sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::SCREEN, "Screen", screenBody );
		m_shaderCompiler.RegisterUniformBuffer( m_uboScreen );

		m_uboScreen->SubData( 0,					sizeof( glm::uint ), &m_settings.renderer.window.size.width );
		m_uboScreen->SubData( sizeof( glm::uint ),	sizeof( glm::uint ), &m_settings.renderer.window.size.height );
	}
}

void CRenderer::UpdateUniformBuffers( const std::shared_ptr<const CEntity> &cameraEntity, const CTimer &timer ) const
{
	/*
	 * Update time into the uniform buffer
	 */

	const glm::uint timeMilliseconds = static_cast<glm::uint>( timer.Time() / 1000 );
	m_uboTimer->SubData( 0,	sizeof( glm::uint ), &timeMilliseconds );

	/*
	 * Update calculated values into the uniform buffer
	 */

	const auto &camera = cameraEntity->Get<CCameraComponent>();

	const glm::vec3 &position = cameraEntity->Transform.Position();
	const glm::vec3 &direction = cameraEntity->Transform.Direction();
	const glm::mat4 &projectionMatrix = camera->ProjectionMatrix();
	const glm::mat4 &viewMatrix = cameraEntity->Transform.ViewMatrix();
	const glm::mat4 &viewProjectionMatrix = camera->ViewProjectionMatrix();

	u32 offset = 0;
	m_uboCamera->SubData( offset,	sizeof( position ),				glm::value_ptr( position ) );
	offset += sizeof( glm::vec4 );
	m_uboCamera->SubData( offset,	sizeof( direction ),			glm::value_ptr( direction ) );
	offset += sizeof( glm::vec4 );
	m_uboCamera->SubData( offset,	sizeof( projectionMatrix ),		glm::value_ptr( projectionMatrix ) );
	offset += sizeof( glm::mat4 );
	m_uboCamera->SubData( offset,	sizeof( viewMatrix ),			glm::value_ptr( viewMatrix ) );
	offset += sizeof( glm::mat4 );
	m_uboCamera->SubData( offset,	sizeof( viewProjectionMatrix ),	glm::value_ptr( viewProjectionMatrix ) );
}

CSamplerManager &CRenderer::SamplerManager()
{
	return( m_samplerManager );
}

COpenGlAdapter &CRenderer::OpenGlAdapter()
{
	return( m_OpenGlAdapter );
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
		framebuffer.Bind();

		const auto &clearColor = scene.ClearColor();
		glClearColor( clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a() );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		UpdateUniformBuffers( cameraEntity, timer );

		/*
		 * set up the draw commands
		 */

		// static list so whe don't need to allocate new memory on every frame
		static DrawCommandList drawCommands;
		drawCommands.clear();

		MTR_BEGIN( "GFX", "fill draw commands list" );
		const auto &cameraFrustum = cameraEntity->Get<CCameraComponent>()->Frustum();

		const auto &cameraPosition = cameraEntity->Transform.Position();

		scene.Each<CModelComponent>( [ &cameraFrustum, &cameraPosition ] ( const std::shared_ptr<const CEntity> &entity )
		{
			const auto &mesh = entity->Get<CModelComponent>()->Mesh().get();

			const auto &transform = entity->Transform;

			// TODO use Octree here
			if( cameraFrustum.IsSphereInside( transform.Position(), glm::length( mesh->BoundingSphereRadiusVector * transform.Scale() ) ) )
			{
				const CMaterial * material = mesh->Material().get();

				drawCommands.emplace_back( mesh, material, material->ShaderProgram().get(), transform.ModelMatrix(), glm::length2( transform.Position() - cameraPosition ) );
			}
		} );
		MTR_END( "GFX", "fill draw commands list" );

		const auto &camera = cameraEntity->Get<CCameraComponent>();

		const glm::mat4 viewMatrix				= camera->ViewMatrix();
		const glm::mat4 viewProjectionMatrix	= camera->ViewProjectionMatrix();

		// TODO multithreaded?
		// sort opaque for material, and then front to back (to reduce overdraw)
		MTR_BEGIN( "GFX", "sort" );
		std::sort( std::begin( drawCommands ), std::end( drawCommands ),	
			[]( const DrawCommand &a, const DrawCommand &b ) -> bool
			{
				if( !a.material->Blending() && b.material->Blending() )
				{
					return( true );
				}
				else if( a.material->Blending() && !b.material->Blending() )
				{
					return( false );
				}
				else if( a.material->Blending() )
				{
					return( a.viewDepth > b.viewDepth );
				}
				else
				{
					if( a.material > b.material )
					{
						return( true );
					}
					else if( a.material < b.material )
					{
						return( false );
					}
					else
					{
						return( a.viewDepth < b.viewDepth );
					}
				}
			} );
		MTR_END( "GFX", "sort" );

		Render( drawCommands, viewMatrix, viewProjectionMatrix );

		framebuffer.Unbind();
	}
}

void CRenderer::DisplayFramebuffer( const CFrameBuffer &framebuffer )
{
	// TODO if we remove this, we get problems with the depth buffer. why is that?
	CGLState::DepthMask( GL_TRUE );

	glBlitNamedFramebuffer( 
		framebuffer.GLID, // src is framebuffer
		0, // dest is screen
		0, 0, framebuffer.Size.width, framebuffer.Size.height, // src bounds
		0, 0, framebuffer.Size.width, framebuffer.Size.height, // dest bounds
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
		GL_NEAREST
	);
}

void CRenderer::Render( const DrawCommandList &drawCommands, const glm::mat4 &viewMatrix, const glm::mat4 &viewProjectionMatrix ) const
{
	MTR_SCOPE( "GFX", "Render" );

	const CMesh * currentMesh = nullptr;
	const CMaterial * currentMaterial = nullptr;
	const CShaderProgram * currentShader = nullptr;

	for( const auto & [ mesh, material, shaderProgram, modelMatrix, viewDepth ] : drawCommands )
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
					glUniformMatrix4fv( location, 1, GL_FALSE, &( viewProjectionMatrix * modelMatrix )[ 0 ][ 0 ] );
					break;

				case EEngineUniform::modelViewMatrix:
					glUniformMatrix4fv( location, 1, GL_FALSE, &( viewMatrix * modelMatrix )[ 0 ][ 0 ] );
					break;

				case EEngineUniform::modelMatrix:
					glUniformMatrix4fv( location, 1, GL_FALSE, &modelMatrix[ 0 ][ 0 ] );
					break;
			}
		}

		mesh->Draw();
	}
}
