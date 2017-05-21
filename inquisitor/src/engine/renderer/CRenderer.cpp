#include "CRenderer.hpp"

#include <algorithm>

#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glbinding/Meta.h>

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"

CRenderer::CRenderer( const CSettings &settings, const CFileSystem &filesystem )
	try :
		m_settings { settings },
		m_textureManager( settings, filesystem, m_OpenGlAdapter ),
		m_samplerManager( settings ),
		m_materialManager( filesystem )
{
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE_ARB );

	glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );

	CreateUniformBuffers();
}
catch( CMaterialManager::Exception &e )
{
	logERROR( "unable to initialize MaterialManager" );
	throw Exception();
}
catch( COpenGlAdapter::Exception &e )
{
	logERROR( "unable to initialize OpenGlAdapter" );
	throw Exception();
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
		m_materialManager.ShaderManager().RegisterUniformBuffer( m_uboCamera );
	}

	{
		const std::string timerBody = "uint time;";

		m_uboTimer = std::make_shared< CUniformBuffer >( sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, "Timer", timerBody );
		m_materialManager.ShaderManager().RegisterUniformBuffer( m_uboTimer );
	}

	{
		const std::string screenBody = 	"uint width;" \
										"uint height;";

		m_uboScreen = std::make_shared< CUniformBuffer >( 2 * sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::SCREEN, "Screen", screenBody );
		m_materialManager.ShaderManager().RegisterUniformBuffer( m_uboScreen );

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

	const glm::vec3 &position = camera->Position();
	const glm::vec3 &direction = camera->Direction();
	const glm::mat4 &projectionMatrix = camera->CalculateProjectionMatrix();
	const glm::mat4 &viewMatrix = camera->CalculateViewMatrix();
	const glm::mat4 &viewProjectionMatrix = camera->CalculateViewProjectionMatrix();

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

void CRenderer::Update( void )
{
	m_materialManager.Update();
	m_textureManager.Update();
}

std::shared_ptr< CImage > CRenderer::GetScreenshot( void ) const
{
	const CSize &size			= m_settings.renderer.window.size;
	const std::uint32_t pitch	= size.width * 3;

	auto pixels = std::make_unique< CImage::PixelBuffer >( pitch * size.height );

	glReadPixels( 0, 0, size.width, size.height, GL_BGR, GL_UNSIGNED_BYTE, static_cast< void* >( pixels->data() ) );

	return( std::make_shared< CImage >( size, size, true, 24, pitch, std::move( pixels ) ) );
}

void CRenderer::ReloadResources( void )
{
	m_textureManager.ReloadTextures();
	m_materialManager.ReloadMaterials();
}

CTextureManager &CRenderer::TextureManager( void )
{
	return( m_textureManager );
}

CSamplerManager &CRenderer::SamplerManager( void )
{
	return( m_samplerManager );
}

CMaterialManager &CRenderer::MaterialManager( void )
{
	return( m_materialManager );
}

void CRenderer::SetClearColor( const CColor &color ) const
{
	glClearColor( color.r(), color.g(), color.b(), color.a() );
}

void CRenderer::Clear( bool colorBuffer, bool depthBuffer ) const
{
	if( colorBuffer && depthBuffer )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
	else if( colorBuffer )
	{
		glClear( GL_COLOR_BUFFER_BIT );
	}
	else if( depthBuffer )
	{
		glClear( GL_DEPTH_BUFFER_BIT );
	}
}

void CRenderer::RenderScene( const CScene &scene, const CTimer &timer ) const
{
	const auto camera = scene.Camera();

	if( !camera )
	{
		logWARNING( "scene has no camera" );
	}
	else
	{
		const auto &frustum = camera->CalculateFrustum();

		UpdateUniformBuffers( camera, timer );

		/*
		 * set up the renderbuckets
		 */

		// static buckets so whe don't need to allocate new memory on every frame
		// get cleared at the end of this function

		static TRenderBucketMaterials renderBucketMaterialsOpaque;
		static TRenderBucketMeshes renderBucketMaterialsTranslucent;

		for( const std::shared_ptr< const CMesh > &mesh : scene.Meshes() )
		{
			if( frustum.IsSphereInside( mesh->Position(), mesh->BoundingSphereRadius() ) )
			{
				if( mesh->Material()->Blending() )
				{
					renderBucketMaterialsTranslucent.push_back( mesh.get() );
				}
				else
				{
					renderBucketMaterialsOpaque[ mesh->Material().get() ].push_back( mesh.get() );
				}
			}
		}

		const glm::mat4 viewProjectionMatrix = camera->CalculateViewProjectionMatrix();

		RenderBucketMaterials( renderBucketMaterialsOpaque, viewProjectionMatrix );

		renderBucketMaterialsOpaque.clear();

		const glm::vec3 &cameraPosition = camera->Position();

		// TODO multithreaded?
		// sort translucent back to front
		std::sort( std::begin( renderBucketMaterialsTranslucent ), std::end( renderBucketMaterialsTranslucent ),	[&cameraPosition]( const CMesh * const a, const CMesh * const b ) -> bool
																												{
																													return( glm::length2( a->Position() - cameraPosition ) > glm::length2( b->Position() - cameraPosition ) );
																												} );

		RenderBucketMeshes( renderBucketMaterialsTranslucent, viewProjectionMatrix );

		renderBucketMaterialsTranslucent.clear();
	}
}

void CRenderer::SetupMaterial( const CMaterial * const material ) const
{
	material->Setup();

	material->Shader()->Use();

	for( const auto & [ location, uniform ] : material->MaterialUniforms() )
	{
		uniform->Set( location );
	}
}

void CRenderer::RenderBucketMeshes( const TRenderBucketMeshes &bucketMeshes, const glm::mat4 &viewProjectionMatrix ) const
{
	for( const auto * bucketMesh : bucketMeshes )
	{
		const CMaterial * const material = bucketMesh->Material().get();

		SetupMaterial( material );

		const auto shader = material->Shader().get();

		RenderMesh( bucketMesh, viewProjectionMatrix, shader );
	}
}

void CRenderer::RenderBucketMaterials( const TRenderBucketMaterials &bucketMaterials, const glm::mat4 &viewProjectionMatrix ) const
{
	for( const auto & [ material, meshes ] : bucketMaterials )
	{
		SetupMaterial( material );

		const auto shader = material->Shader().get();

		for( const auto * mesh : meshes )
		{
			RenderMesh( mesh, viewProjectionMatrix, shader );
		}
	}
}

void CRenderer::RenderMesh( const CMesh * const mesh, const glm::mat4 &viewProjectionMatrix, const CShaderProgram * const shader ) const
{
	mesh->BindTextures();

	for( const auto & [ location, engineUniform ] : shader->RequiredEngineUniforms() )
	{
		switch( engineUniform )
		{
			case EEngineUniform::modelViewProjectionMatrix:
				glUniformMatrix4fv( location, 1, GL_FALSE, &( viewProjectionMatrix * mesh->ModelMatrix() )[ 0 ][ 0 ] );
				break;

			case EEngineUniform::modelMatrix:
				glUniformMatrix4fv( location, 1, GL_FALSE, &mesh->ModelMatrix()[ 0 ][ 0 ] );
				break;
		}
	}

	const CVAO &vao = mesh->VAO();

	vao.Bind();

	vao.Draw();
}
