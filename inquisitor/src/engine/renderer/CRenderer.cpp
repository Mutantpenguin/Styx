#include "CRenderer.hpp"

#include <algorithm>

#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glbinding/Meta.h>

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"

CRenderer::CRenderer( const CSettings &settings, const CFileSystem &filesystem, CResourceCacheManager &resourceCacheManager )
	try :
		m_settings { settings },
		m_resourceCacheManager { resourceCacheManager },
		m_textureCache { std::make_shared< CTextureCache >( settings, filesystem, m_OpenGlAdapter ) },
		m_samplerManager( settings ),
		m_shaderManager( filesystem ),
		m_materialManager( filesystem, m_shaderManager )
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
													"uniform sampler2D screenTexture;" \
													"void main()" \
													"{" \
													"    color = texture( screenTexture, UV );" \
													"}";

		const std::shared_ptr< CMaterial > materialFrameBuffer = std::make_shared< CMaterial >();
		materialFrameBuffer->Shader( m_shaderManager.CreateProgramFromStrings( vertexShaderString, fragmentShaderString ) );

		const CMesh::TTextures frameBufferMeshTextures = { { "screenTexture", std::make_shared< CMeshTexture >( nullptr, nullptr ) } };

		m_meshFrameBuffer = std::make_unique< CMesh >( GL_TRIANGLE_STRIP, Primitives::quad, materialFrameBuffer, frameBufferMeshTextures );
	}

	m_resourceCacheManager.Register< CTexture >( m_textureCache );

	logINFO( "renderer was initialized" );
}
catch( CMaterialManager::Exception &e )
{
	logERROR( "unable to initialize MaterialManager" );
	throw Exception();
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

CRenderer::~CRenderer( void )
{
	logINFO( "renderer is shutting down" );

	m_resourceCacheManager.DeRegister( m_textureCache );
}

void CRenderer::CreateUniformBuffers( void )
{
	{
		const std::string cameraBody =	"vec3 position;" \
										"vec3 direction;" \
										"mat4 projectionMatrix;" \
										"mat4 viewMatrix;" \
										"mat4 viewProjectionMatrix;";

		m_uboCamera = std::make_shared< CUniformBuffer >( ( 2 * sizeof( glm::vec4 ) ) + ( 3 * sizeof( glm::mat4 ) ), GL_DYNAMIC_DRAW, EUniformBufferLocation::CAMERA, "Camera", cameraBody );
		m_shaderManager.RegisterUniformBuffer( m_uboCamera );
	}

	{
		const std::string timerBody = "uint time;";

		m_uboTimer = std::make_shared< CUniformBuffer >( sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, "Timer", timerBody );
		m_shaderManager.RegisterUniformBuffer( m_uboTimer );
	}

	{
		const std::string screenBody = 	"uint width;" \
										"uint height;";

		m_uboScreen = std::make_shared< CUniformBuffer >( 2 * sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::SCREEN, "Screen", screenBody );
		m_shaderManager.RegisterUniformBuffer( m_uboScreen );

		m_uboScreen->SubData( 0,					sizeof( glm::uint ), &m_settings.renderer.window.size.width );
		m_uboScreen->SubData( sizeof( glm::uint ),	sizeof( glm::uint ), &m_settings.renderer.window.size.height );
	}
}

void CRenderer::UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const CTimer &timer ) const
{
	/*
	 * Update time into the uniform buffer
	 */

	const glm::uint timeMilliseconds = static_cast< glm::uint >( timer.Time() / 1000 );
	m_uboTimer->SubData( 0,	sizeof( glm::uint ), &timeMilliseconds );

	/*
	 * Update calculated values into the uniform buffer
	 */

	const glm::vec3 &position = camera->Transform.Position();
	const glm::vec3 &direction = camera->Direction();
	const glm::mat4 &projectionMatrix = camera->ProjectionMatrix();
	const glm::mat4 &viewMatrix = camera->Transform.ViewMatrix();
	const glm::mat4 &viewProjectionMatrix = camera->ViewProjectionMatrix();

	std::uint32_t offset = 0;
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

CSamplerManager &CRenderer::SamplerManager( void )
{
	return( m_samplerManager );
}

CMaterialManager &CRenderer::MaterialManager( void )
{
	return( m_materialManager );
}

COpenGlAdapter &CRenderer::OpenGlAdapter( void )
{
	return( m_OpenGlAdapter );
}

void CRenderer::RenderSceneToFramebuffer( const CScene &scene, const CFrameBuffer &framebuffer, const CTimer &timer ) const
{
	const auto &camera = scene.Camera();

	if( !camera )
	{
		logWARNING( "scene has no camera" );
	}
	else
	{
		framebuffer.Bind();

		const auto &clearColor = scene.ClearColor();
		glClearColor( clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a() );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		UpdateUniformBuffers( camera, timer );

		/*
		 * set up the renderbuckets
		 */

		// static buckets so whe don't need to allocate new memory on every frame
		// get cleared at the end of this function

		static TRenderBucket renderBucketMaterialsOpaque;
		renderBucketMaterialsOpaque.clear();

		static TRenderBucket renderBucketMaterialsTranslucent;
		renderBucketMaterialsTranslucent.clear();

		for( const auto &meshInstance : scene.Meshes() )
		{
			if( meshInstance.mesh->Material()->Blending() )
			{
				renderBucketMaterialsTranslucent.push_back( meshInstance );
			}
			else
			{
				renderBucketMaterialsOpaque.push_back( meshInstance );
			}
		}

		const glm::mat4 viewProjectionMatrix = camera->ViewProjectionMatrix();

		/* TODO this makes everything slower
		std::sort( std::begin( renderBucketMaterialsOpaque ), std::end( renderBucketMaterialsOpaque ),	[]( const CScene::MeshInstance &a, const CScene::MeshInstance &b ) -> bool
																										{
																											return( a.mesh->Material() > b.mesh->Material() );
																										} );
		//*/

		RenderBucket( renderBucketMaterialsOpaque, viewProjectionMatrix );

		const glm::vec3 &cameraPosition = camera->Transform.Position();

		// TODO multithreaded?
		// sort translucent back to front
		std::sort( std::begin( renderBucketMaterialsTranslucent ), std::end( renderBucketMaterialsTranslucent ),	[&cameraPosition]( const CScene::MeshInstance &a, const CScene::MeshInstance &b ) -> bool
																													{
																														return( glm::length2( a.Transform.Position() - cameraPosition ) > glm::length2( b.Transform.Position() - cameraPosition ) );
																													} );

		RenderBucket( renderBucketMaterialsTranslucent, viewProjectionMatrix );

		framebuffer.Unbind();
	}
}

void CRenderer::DisplayFramebuffer( const CFrameBuffer &framebuffer )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_meshFrameBuffer->ChangeTexture( "screenTexture", framebuffer.ColorTexture(), m_samplerManager.GetFromType( CSampler::SamplerType::REPEAT_2D ) );

	m_meshFrameBuffer->Material()->Setup();

	m_meshFrameBuffer->BindTextures();

	const CVAO &vao = m_meshFrameBuffer->VAO();

	vao.Bind();

	vao.Draw();
}

void CRenderer::RenderBucket( const TRenderBucket &bucketMaterials, const glm::mat4 &viewProjectionMatrix ) const
{
	const CMesh * currentMesh = nullptr;
	const CMaterial * currentMaterial = nullptr;

	const CShaderProgram * currentShader = nullptr;

	for( const auto & [ mesh, transform ] : bucketMaterials )
	{
		if( currentMesh != mesh )
		{
			currentMesh = mesh;

			const auto material = mesh->Material();

			if( currentMaterial != material.get() )
			{
				currentMaterial = material.get();
				material->Setup();

				currentShader = material->Shader().get();
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

[[nodiscard]] glm::mat4 CRenderer::CalculateModelMatrix( const CTransformComponent &transform ) const
{
	glm::mat4 modelMatrix = glm::mat4();

	modelMatrix = glm::translate( modelMatrix, transform.Position() );

	modelMatrix = modelMatrix * glm::toMat4( transform.Orientation() );

	modelMatrix = glm::scale( modelMatrix, transform.Scale() );

	return( modelMatrix );
}

