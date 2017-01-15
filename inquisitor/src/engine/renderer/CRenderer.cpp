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
		m_samplerManager( settings ),
		m_materialmanager( settings, filesystem, m_samplerManager, m_OpenGlAdapter )
{
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

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
	const std::string cameraBody =	"vec3 position;" \
									"vec3 direction;" \
									"mat4 projectionMatrix;" \
									"mat4 viewMatrix;" \
									"mat4 viewProjectionMatrix;";

	m_uboCamera = std::make_shared< CUniformBuffer >( ( 2 * sizeof( glm::vec4 ) ) + ( 3 * sizeof( glm::mat4 ) ), GL_DYNAMIC_DRAW, EUniformBufferLocation::CAMERA, "Camera", cameraBody );
	m_materialmanager.ShaderManager().RegisterUniformBuffer( m_uboCamera );

	const std::string timerBody = "uint time;";

	m_uboTimer = std::make_shared< CUniformBuffer >( sizeof( glm::uint ), GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, "Timer", timerBody );
	m_materialmanager.ShaderManager().RegisterUniformBuffer( m_uboTimer );
}

void CRenderer::UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const std::uint64_t time ) const
{
	/*
	 * Update time into the uniform buffer
	 */

	const glm::uint timeMilliseconds = static_cast< glm::uint >( time / 1000 );
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
	m_materialmanager.Update();
}

std::shared_ptr< CImage > CRenderer::GetScreenshot( void ) const
{
	const CSize &size			= m_settings.renderer.window.size;
	const std::uint32_t pitch	= size.width * 3;

	auto pixels = std::make_unique< CImage::PixelBuffer >( pitch * size.height );

	glReadPixels( 0, 0, size.width, size.height, GL_BGR, GL_UNSIGNED_BYTE, static_cast< void* >( pixels->data() ) );

	return( std::make_shared< CImage >( size, size, true, 24, pitch, std::move( pixels ) ) );
}

std::shared_ptr< CMaterial > CRenderer::LoadMaterial( const std::string &path )
{
	return( m_materialmanager.LoadMaterial( path ) );
}

void CRenderer::SetClearColor( const CColor &color )
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

void CRenderer::RenderScene( const CScene &scene, const std::uint64_t time ) const
{
	const auto camera = scene.Camera();

	if( !camera )
	{
		logWARNING( "scene has no camera" );
	}
	else
	{
		const auto &frustum = camera->CalculateFrustum();

		UpdateUniformBuffers( camera, time );

		/*
		 * set up the renderqueues
		 */

		// static queues so whe don't need to allocate new memory on every frame
		// get cleared at the end of this function

		static TRenderQueue renderQueueOpaque;
		static TRenderQueue renderQueueTranslucent;

		for( const std::shared_ptr< const CMesh > &mesh : scene.Meshes() )
		{
			if( frustum.IsSphereInside( mesh->Position(), mesh->BoundingSphereRadius() ) )
			{
				if( mesh->Material()->Blending() )
				{
					renderQueueTranslucent.push_back( mesh.get() );
				}
				else
				{
					renderQueueOpaque.push_back( mesh.get() );
				}
			}
		}

		const glm::vec3 &cameraPosition = camera->Position();
		const glm::mat4 viewProjectionMatrix = camera->CalculateViewProjectionMatrix();

		// sort opaque front to back
		std::sort( std::begin( renderQueueOpaque ), std::end( renderQueueOpaque ),	[&]( const CMesh * const a, const CMesh * const b ) -> bool
																					{
																						return( glm::length2( a->Position() - cameraPosition ) < glm::length2( b->Position() - cameraPosition ) );
																					} );

		// sort translucent back to front
		std::sort( std::begin( renderQueueTranslucent ), std::end( renderQueueTranslucent ),	[&]( const CMesh * const a, const CMesh * const b ) -> bool
																								{
																									return( glm::length2( a->Position() - cameraPosition ) > glm::length2( b->Position() - cameraPosition ) );
																								} );

		for( const CMesh * const mesh : renderQueueOpaque )
		{
			RenderMesh( viewProjectionMatrix, mesh );
		}

		for( const CMesh * const mesh : renderQueueTranslucent )
		{
			RenderMesh( viewProjectionMatrix, mesh );
		}

		renderQueueOpaque.clear();
		renderQueueTranslucent.clear();
	}
}

void CRenderer::RenderMesh( const glm::mat4 &viewProjectionMatrix, const CMesh * const mesh ) const
{
	const std::shared_ptr< const CMaterial > material = mesh->Material();

	material->Setup();

	const CVAO &vao = mesh->VAO();

	vao.Bind();

	const auto shader = material->Shader();

	shader->Use();

	for( const auto &requiredEngineUniform : shader->RequiredEngineUniforms() )
	{
		const auto location = requiredEngineUniform.first;

		switch( requiredEngineUniform.second )
		{
			case EEngineUniform::modelViewProjectionMatrix:
				glUniformMatrix4fv( location, 1, GL_FALSE, &( viewProjectionMatrix * mesh->ModelMatrix() )[ 0 ][ 0 ] );
				break;

			case EEngineUniform::modelMatrix:
				glUniformMatrix4fv( location, 1, GL_FALSE, &mesh->ModelMatrix()[ 0 ][ 0 ] );
				break;
		}
	}

	std::uint8_t textureUnit = 0;
	for( const auto &samplerData : material->SamplerData() )
	{
		const auto location = samplerData.first;

		glUniform1i( location, textureUnit );

		samplerData.second->BindToUnit( textureUnit );

		textureUnit++;
	}

	for( const auto &uniform : material->MaterialUniforms() )
	{
		const auto location = uniform.first;

		uniform.second->Set( location );
	}

	vao.Draw();
}
