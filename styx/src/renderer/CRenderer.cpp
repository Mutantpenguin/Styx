#include "CRenderer.hpp"

#include <algorithm>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glbinding-aux/Meta.h>

#include "external/minitrace/minitrace.h"

#include "src/renderer/components/CModelComponent.hpp"
#include "src/scene/components/camera/CCameraComponent.hpp"

#include "src/logger/CLogger.hpp"

CRenderer::CRenderer( const CSettings &settings, const CFileSystem &filesystem, CResourceCacheManager &resourceCacheManager )
	try :
		m_settings { settings },
		m_resourceCacheManager { resourceCacheManager },
		m_samplerManager( settings ),
		m_shaderCache{ std::make_shared< CShaderCache >( filesystem, m_shaderCompiler ) },
		m_shaderManager( filesystem, m_shaderCompiler, m_resourceCacheManager ),
		m_textureCache { std::make_shared< CTextureCache >( settings, filesystem, m_OpenGlAdapter ) },
		m_materialCache { std::make_shared< CMaterialCache >( filesystem, m_shaderManager ) }
{
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );

	glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );

	CreateUniformBuffers();

	{
		// TODO write comments
		const std::string vertexShaderString =	"out vec2 UV;" \
												"void main()" \
												"{" \
												"    gl_Position = vec4( position.x, position.y, 0.0, 1.0 );" \
												"    UV = texcoord;" \
												"}";
		const std::string fragmentShaderString =	"out vec4 color;" \
													"in vec2 UV;" \
													"uniform sampler2D " + m_slotNameFrameBuffer + ";" \
													"void main()" \
													"{" \
													"    color = texture( " + m_slotNameFrameBuffer + ", UV );" \
													"}";

		const auto vertexShader = std::make_shared<CShader>();
		if( !m_shaderCompiler.Compile( vertexShader, GL_VERTEX_SHADER, vertexShaderString ) )
		{
			throw std::exception( "couldn't create vertex shader for framebuffer" );
		}

		const auto fragmentShader = std::make_shared<CShader>();
		if( !m_shaderCompiler.Compile( fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderString ) )
		{
			throw std::exception( "couldn't create fragment shader for framebuffer" );
		}

		const std::shared_ptr< CMaterial > materialFrameBuffer = std::make_shared< CMaterial >();
		materialFrameBuffer->ShaderProgram( m_shaderManager.CreateProgramFromShaders( vertexShader, fragmentShader ) );

		const CMesh::TMeshTextureSlots frameBufferMeshTextureSlots = { { m_slotNameFrameBuffer, std::make_shared< CMeshTextureSlot >( nullptr, m_samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) ) } };

		m_meshFrameBuffer = std::make_unique< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialFrameBuffer, frameBufferMeshTextureSlots );
	}

	m_resourceCacheManager.Register< CTexture >( m_textureCache );
	m_resourceCacheManager.Register< CMaterial >( m_materialCache );
	m_resourceCacheManager.Register< CShader >( m_shaderCache );

	logINFO( "renderer was initialized" );
}
catch( CShaderManager::Exception &e )
{
	logERROR( "unable to initialize ShaderManager" );
	throw Exception();
}
catch( COpenGlAdapter::Exception &e )
{
	logERROR( "unable to initialize OpenGlAdapter" );
	throw Exception();
}

CRenderer::~CRenderer()
{
	logINFO( "renderer is shutting down" );

	m_resourceCacheManager.DeRegister( m_shaderCache );
	m_resourceCacheManager.DeRegister( m_materialCache );
	m_resourceCacheManager.DeRegister( m_textureCache );
}

void CRenderer::CreateUniformBuffers()
{
	{
		const std::string cameraBody =	"vec3 position;" \
										"vec3 direction;" \
										"mat4 projectionMatrix;" \
										"mat4 viewMatrix;" \
										"mat4 viewProjectionMatrix;";

		m_uboCamera = std::make_shared< CUniformBuffer >( ( 2 * sizeof( glm::vec4 ) ) + ( 3 * sizeof( glm::mat4 ) ), GL_DYNAMIC_DRAW, EUniformBufferLocation::CAMERA, "Camera", cameraBody );
		m_shaderCompiler.RegisterUniformBuffer( m_uboCamera );
	}

	{
		const std::string timerBody = "uint time;";

		m_uboTimer = std::make_shared< CUniformBuffer >( sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, "Timer", timerBody );
		m_shaderCompiler.RegisterUniformBuffer( m_uboTimer );
	}

	{
		const std::string screenBody = 	"uint width;" \
										"uint height;";

		m_uboScreen = std::make_shared< CUniformBuffer >( 2 * sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::SCREEN, "Screen", screenBody );
		m_shaderCompiler.RegisterUniformBuffer( m_uboScreen );

		m_uboScreen->SubData( 0,					sizeof( glm::uint ), &m_settings.renderer.window.size.width );
		m_uboScreen->SubData( sizeof( glm::uint ),	sizeof( glm::uint ), &m_settings.renderer.window.size.height );
	}
}

void CRenderer::UpdateUniformBuffers( const std::shared_ptr< const CEntity > &cameraEntity, const CTimer &timer ) const
{
	/*
	 * Update time into the uniform buffer
	 */

	const glm::uint timeMilliseconds = static_cast< glm::uint >( timer.Time() / 1000 );
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
		 * set up the renderbuckets
		 */

		// static buckets so whe don't need to allocate new memory on every frame

		static TRenderBucket renderBucketMaterialsOpaque;
		renderBucketMaterialsOpaque.clear();

		static TRenderBucket renderBucketMaterialsTranslucent;
		renderBucketMaterialsTranslucent.clear();

		MTR_BEGIN( "GFX", "fill render buckets" );
		const auto &frustum = cameraEntity->Get<CCameraComponent>()->Frustum();

		scene.Each<CModelComponent>( [&frustum,&cameraEntity] ( const std::shared_ptr<const CEntity> &entity )
		{
			const auto &mesh = entity->Get<CModelComponent>()->Mesh().get();

			// TODO use Octree here
			if( frustum.IsSphereInside( entity->Transform.Position(), glm::length( mesh->BoundingSphereRadiusVector() * entity->Transform.Scale() ) ) )
			{
				if( mesh->Material()->Blending() )
				{
					renderBucketMaterialsTranslucent.emplace_back( mesh, entity->Transform, glm::length2( entity->Transform.Position() - cameraEntity->Transform.Position() ) );
				}
				else
				{
					renderBucketMaterialsOpaque.emplace_back( mesh, entity->Transform, glm::length2( entity->Transform.Position() - cameraEntity->Transform.Position() ) );
				}
			}
		} );
		MTR_END( "GFX", "fill render buckets" );

		const auto &camera = cameraEntity->Get<CCameraComponent>();

		const glm::mat4 viewProjectionMatrix = camera->ViewProjectionMatrix();

		// TODO multithreaded?
		// sort opaque for material, and then front to back (to reduce overdraw)
		MTR_BEGIN( "GFX", "sort opaque" );
		std::sort( std::begin( renderBucketMaterialsOpaque ), std::end( renderBucketMaterialsOpaque ),	[]( const MeshInstance &a, const MeshInstance &b ) -> bool
																										{
																											return( ( a.mesh->Material() > b.mesh->Material() )
																													||
																													( ( a.mesh->Material() == b.mesh->Material() ) && ( a.viewDepth < b.viewDepth ) ) );
																										} );
		MTR_END( "GFX", "sort opaque" );

		RenderBucket( renderBucketMaterialsOpaque, viewProjectionMatrix );

		// TODO multithreaded?
		// sort translucent back to front
		MTR_BEGIN( "GFX", "sort translucent" );
		std::sort( std::begin( renderBucketMaterialsTranslucent ), std::end( renderBucketMaterialsTranslucent ),	[]( const MeshInstance &a, const MeshInstance &b ) -> bool
																													{
																														return( a.viewDepth > b.viewDepth );
																													} );
		MTR_END( "GFX", "sort translucent" );

		RenderBucket( renderBucketMaterialsTranslucent, viewProjectionMatrix );

		framebuffer.Unbind();
	}
}

void CRenderer::DisplayFramebuffer( const CFrameBuffer &framebuffer )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_meshFrameBuffer->ChangeTexture( m_slotNameFrameBuffer, framebuffer.ColorTexture() );

	m_meshFrameBuffer->Material()->Activate();

	m_meshFrameBuffer->BindTextures();

	const CVAO &vao = m_meshFrameBuffer->VAO();

	vao.Bind();

	vao.Draw();
}

void CRenderer::RenderBucket( const TRenderBucket &bucketMaterials, const glm::mat4 &viewProjectionMatrix ) const
{
	MTR_SCOPE( "GFX", "RenderBucket" );

	const CMesh * currentMesh = nullptr;
	const CMaterial * currentMaterial = nullptr;

	const CShaderProgram * currentShader = nullptr;

	for( const auto & [ mesh, transform, viewDepth ] : bucketMaterials )
	{
		if( currentMesh != mesh )
		{
			currentMesh = mesh;

			const auto material = mesh->Material();

			if( currentMaterial != material.get() )
			{
				currentMaterial = material.get();
				material->Activate();

				currentShader = material->ShaderProgram().get();
			}

			mesh->BindTextures();

			mesh->VAO().Bind();
		}

		for( const auto & [ location, engineUniform ] : currentShader->RequiredEngineUniforms() )
		{
			switch( engineUniform )
			{
				case EEngineUniform::modelViewProjectionMatrix:
					glUniformMatrix4fv( location, 1, GL_FALSE, &( viewProjectionMatrix * CalculateModelMatrix( transform ) )[ 0 ][ 0 ] );
					break;

				case EEngineUniform::modelMatrix:
					glUniformMatrix4fv( location, 1, GL_FALSE, &CalculateModelMatrix( transform )[ 0 ][ 0 ] );
					break;
			}
		}

		mesh->VAO().Draw();
	}
}

[[nodiscard]] glm::mat4 CRenderer::CalculateModelMatrix( const CTransform &transform ) const
{
	glm::mat4 modelMatrix = glm::mat4( 1.0f );

	modelMatrix = glm::translate( modelMatrix, transform.Position() );

	modelMatrix = modelMatrix * glm::toMat4( transform.Orientation() );

	modelMatrix = glm::scale( modelMatrix, transform.Scale() );

	return( modelMatrix );
}

