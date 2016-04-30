#include "CRenderer.hpp"

#include <algorithm>

#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glbinding/Binding.h>
#include <glbinding/Meta.h>
#include <glbinding/Version.h>
#include <glbinding/ContextInfo.h>

#include "CGLState.hpp"

#include "../logger/CLogger.hpp"

CRenderer::CRenderer( const CSettings &settings, const CFileSystem &filesystem ) :
	m_settings { settings },
	m_samplerManager( settings ),
	m_materialmanager( settings, filesystem, m_samplerManager )
{
	glbinding::Binding::initialize();

	// TODO query all capabilities in this class
	m_rendererCapabilities.Init();

	LOG( logINFO ) << "OpenGL Version:  " << glbinding::ContextInfo::version();
	LOG( logINFO ) << "OpenGL Vendor:   " << glbinding::ContextInfo::vendor();
	LOG( logINFO ) << "OpenGL Renderer: " << glbinding::ContextInfo::renderer();
	LOG( logINFO ) << "OpenGL Revision: " << glbinding::Meta::glRevision() << " (gl.xml)";
	LOG( logINFO ) << "GLSL Version:    " << reinterpret_cast< const char* >( glGetString( GL_SHADING_LANGUAGE_VERSION ) );

	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_maxCombinedTextureImageUnits );
	if( m_maxCombinedTextureImageUnits < CShaderManager::requiredCombinedTextureImageUnits )
	{
		LOG( logERROR ) << "not enough combined texture image units: " << m_maxCombinedTextureImageUnits << " found but " << CShaderManager::requiredCombinedTextureImageUnits << " needed";
		throw std::exception();
	}
	LOG( logDEBUG ) << "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS is " << m_maxCombinedTextureImageUnits;

	const auto requiredOpenGLExtensions = {	GLextension::GL_EXT_texture_filter_anisotropic,
											GLextension::GL_ARB_texture_storage,
											GLextension::GL_ARB_direct_state_access,
											GLextension::GL_ARB_explicit_uniform_location,
											GLextension::GL_ARB_shading_language_420pack,
											GLextension::GL_ARB_program_interface_query };

	for( const auto &extension : requiredOpenGLExtensions )
	{
		if( !m_rendererCapabilities.isSupported( extension ) )
		{
			LOG( logERROR ) << "required extension " << glbinding::Meta::getString( extension ) << " not supported";
			throw std::exception();
		}
	}

	#ifdef INQ_DEBUG
		if( m_rendererCapabilities.isSupported( GLextension::GL_KHR_debug )
			||
			m_rendererCapabilities.isSupported( GLextension::GL_ARB_debug_output ) )
		{
			glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );

			glDebugMessageCallback(	[]( GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei, const GLchar* message, const void* )
									{
										const e_loglevel loglvl = ( GL_DEBUG_SEVERITY_HIGH == severity ) ? logERROR : logWARNING;

										LOG( loglvl ) << "OpenGL ERROR";
										LOG( loglvl ) << "Source   : " << glbinding::Meta::getString( source );
										LOG( loglvl ) << "Type     : " << glbinding::Meta::getString( type );
										LOG( loglvl ) << "ID       : " << id;
										LOG( loglvl ) << "Severity : " << glbinding::Meta::getString( severity );
										LOG( loglvl ) << "Message  : " << message;
									}, nullptr );
		}
		else
		{
			LOG( logWARNING ) << "neither " << glbinding::Meta::getString( GLextension::GL_KHR_debug ) << " nor " << glbinding::Meta::getString( GLextension::GL_ARB_debug_output ) << " are available";
		}
	#endif

	LOG( logINFO ) << "video memory:";

	const bool supports_GL_NVX_gpu_memory_info = m_rendererCapabilities.isSupported( GLextension::GL_NVX_gpu_memory_info );
	const bool supports_GL_ATI_meminfo         = m_rendererCapabilities.isSupported( GLextension::GL_ATI_meminfo );
	if( !supports_GL_NVX_gpu_memory_info && !supports_GL_ATI_meminfo )
	{
		LOG( logINFO ) << "  not available";
	}
	else
	{
		if( supports_GL_NVX_gpu_memory_info )
		{
			GLint dedicatedMemKb = 0;
			glGetIntegerv( GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicatedMemKb );

			GLint totalAvailableMemKb = 0;
			glGetIntegerv( GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalAvailableMemKb );

			GLint currentlyAvailableMemKb = 0;
			glGetIntegerv( GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currentlyAvailableMemKb );

			LOG( logINFO ) << "  total dedicated:     " << dedicatedMemKb / 1024 << " MiB";
			LOG( logINFO ) << "  total available:     " << totalAvailableMemKb / 1024 << " MiB";
			LOG( logINFO ) << "  currently available: " << currentlyAvailableMemKb / 1024 << " MiB";
		}

		if( supports_GL_ATI_meminfo )
		{
			GLint vboFreeMemKb = 0;
			glGetIntegerv( GL_VBO_FREE_MEMORY_ATI, &vboFreeMemKb );

			GLint textureFreeMemKb = 0;
			glGetIntegerv( GL_TEXTURE_FREE_MEMORY_ATI, &textureFreeMemKb );

			GLint renderbufferFreeMemKb = 0;
			glGetIntegerv( GL_RENDERBUFFER_FREE_MEMORY_ATI, &renderbufferFreeMemKb );

			LOG( logINFO ) << "    free for VBOs:           " << vboFreeMemKb / 1024 << " MiB";
			LOG( logINFO ) << "    free for textures:       " << textureFreeMemKb / 1024 << " MiB";
			LOG( logINFO ) << "    free for render buffers: " << renderbufferFreeMemKb / 1024 << " MiB";
		}
	}

	if( !m_materialmanager.Init( m_rendererCapabilities ) )
	{
		LOG( logERROR ) << "unable to initialize MaterialManager";
		throw std::exception();
	}

	if( !m_samplerManager.Init( ) )
	{
		LOG( logERROR ) << "unable to initialize SamplerManager";
		throw std::exception();
	}

	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );

	CreateUniformBuffers();
}

void CRenderer::CreateUniformBuffers( void )
{
	const std::string cameraPlaceholder = "[uniformBlockCamera]";
	const std::string cameraSource =	"layout ( std140, binding = [LOCATION] ) uniform camera\n" \
										"{\n" \
										"	vec3 position;\n" \
										"	vec3 direction;\n" \
										"	mat4 projectionMatrix;\n" \
										"	mat4 viewMatrix;\n" \
										"	mat4 viewProjectionMatrix;\n" \
										"} cam;";

	m_uboCamera = std::make_shared< CUniformBuffer >( ( 2 * sizeof( glm::vec4 ) ) + ( 3 * sizeof( glm::mat4 ) ), nullptr, GL_DYNAMIC_DRAW, EUniformBufferLocation::CAMERA, cameraPlaceholder, cameraSource );
	m_materialmanager.ShaderManager().RegisterUniformBuffer( m_uboCamera );

	const std::string timerPlaceholder = "[uniformBlockTimer]";
	const std::string timerSource =	"layout ( std140, binding = [LOCATION] ) uniform camera\n" \
									"{\n" \
									"	uint time;\n" \
									"	vec3 direction;\n" \
									"	mat4 projectionMatrix;\n" \
									"	mat4 viewMatrix;\n" \
									"	mat4 viewProjectionMatrix;\n" \
									"} timer;";

	m_uboTimer = std::make_shared< CUniformBuffer >( sizeof( glm::uint ), nullptr, GL_DYNAMIC_DRAW, EUniformBufferLocation::TIME, timerPlaceholder, timerSource );
	m_materialmanager.ShaderManager().RegisterUniformBuffer( m_uboTimer );
}

void CRenderer::UpdateUniformBuffers( const std::shared_ptr< const CCamera > &camera, const std::uint64_t time )
{
	/*
	 * Update calculated values into the uniform buffer
	 */

	const glm::vec3 &position = camera->Position();
	const glm::vec3 &direction = camera->Direction();
	const glm::mat4 &projectionMatrix = camera->ProjectionMatrix();
	const glm::mat4 &viewMatrix = camera->ViewMatrix();
	const glm::mat4 &viewProjectionMatrix = camera->ViewProjectionMatrix();

	std::uint16_t offset = 0;
	m_uboCamera->SubData( offset,		sizeof( position ),				glm::value_ptr( position ) );
	offset += sizeof( glm::vec4 );
	m_uboCamera->SubData( offset,		sizeof( direction ),			glm::value_ptr( direction ) );
	offset += sizeof( glm::vec4 );
	m_uboCamera->SubData( offset,		sizeof( projectionMatrix ),		glm::value_ptr( projectionMatrix ) );
	offset += sizeof( glm::mat4 );
	m_uboCamera->SubData( offset,		sizeof( viewMatrix ),			glm::value_ptr( viewMatrix ) );
	offset += sizeof( glm::mat4 );
	m_uboCamera->SubData( offset,		sizeof( viewProjectionMatrix ),	glm::value_ptr( viewProjectionMatrix ) );

	/*
	 * Update time into the uniform buffer
	 */

	const glm::uint timeMilliseconds = static_cast< glm::uint >( time / 1000 );
	m_uboTimer->SubData( 0,	sizeof( glm::uint ), &timeMilliseconds );
}

void CRenderer::Update( const float delta )
{
	m_materialmanager.Update( delta );
}

std::shared_ptr< CImage > CRenderer::GetScreenshot( void ) const
{
	const CSize &size			= m_settings.renderer.window.size;
	const std::uint32_t pitch	= size.width * 3;

	std::unique_ptr< CImage::PixelBuffer > pixels = std::make_unique< CImage::PixelBuffer >( pitch * size.height );

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

void CRenderer::RenderScene( const CScene &scene, const std::uint64_t time )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	std::shared_ptr< CCamera > camera = scene.Camera();

	if( !camera )
	{
		LOG( logWARNING ) << "scene has no camera";
	}
	else
	{
		camera->Update();

		UpdateUniformBuffers( camera, time );

		/*
		 * set up the renderqueues
		 */

		// Allocate enough memory to hold every object.
		// This wastes quite a bit of memory, but has the benefit that we only need to allocate memory once.
		TRenderQueue renderQueueOpaque;
		renderQueueOpaque.reserve( scene.Meshes().size() );
		TRenderQueue renderQueueTranslucent;
		renderQueueTranslucent.reserve( scene.Meshes().size() );

		for( const std::shared_ptr< const CMesh > &mesh : scene.Meshes() )
		{
			if( camera->Frustum().IsSphereInside( mesh->Position(), mesh->BoundingSphereRadius() ) )
			{
				if( mesh->Material()->Blending() )
				{
					renderQueueTranslucent.push_back( mesh );
				}
				else
				{
					renderQueueOpaque.push_back( mesh );
				}
			}
		}

		const glm::vec3 &cameraPosition = camera->Position();

		// sort opaque front to back
		std::sort( renderQueueOpaque.begin(), renderQueueOpaque.end(),	[&]( const std::shared_ptr< const CMesh > &a, const std::shared_ptr< const CMesh > &b ) -> bool
																		{
																			return( glm::length2( a->Position() - cameraPosition ) < glm::length2( b->Position() - cameraPosition ) );
																		} );

		// sort translucent back to front
		std::sort( renderQueueTranslucent.begin(), renderQueueTranslucent.end(),	[&]( const std::shared_ptr< const CMesh > &a, const std::shared_ptr< const CMesh > &b ) -> bool
																					{
																						return( glm::length2( a->Position() - cameraPosition ) > glm::length2( b->Position() - cameraPosition ) );
																					} );

		for( const std::shared_ptr< const CMesh > &mesh : renderQueueOpaque )
		{
			RenderMesh( camera, mesh );
		}

		for( const std::shared_ptr< const CMesh > &mesh : renderQueueTranslucent )
		{
			RenderMesh( camera, mesh );
		}
	}
}

void CRenderer::RenderMesh( const std::shared_ptr< const CCamera > &camera, const std::shared_ptr< const CMesh > &mesh ) const
{
	const std::shared_ptr< const CMaterial > material = mesh->Material();

	CGLState::CullFace( material->m_bCullFace, material->m_cullfacemode );
	CGLState::PolygonMode( material->m_polygonmode );
	CGLState::Blending( material->m_blending, material->m_blendSrc, material->m_blendDst );

	const CVAO &vao = mesh->VAO();

	vao.Bind();

	for( const std::shared_ptr< const CMaterialLayer > &layer : material->Layers() )
	{
		CGLState::UseProgram( layer->m_shader->m_program );

		for( const auto &uniform : layer->m_shader->m_requiredReservedUniforms )
		{
			const GLuint uniformLocation = static_cast< GLuint >( uniform );

			switch( uniform )
			{
				case EReservedUniformLocations::modelViewProjectionMatrix:
					glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, &( camera->ViewProjectionMatrix() * mesh->ModelMatrix() )[ 0 ][ 0 ] );
					break;

				case EReservedUniformLocations::textureMatrix:
					glUniformMatrix3fv( uniformLocation, 1, GL_FALSE, &layer->m_textureMatrix[ 0 ][ 0 ] );
					break;

				case EReservedUniformLocations::modelMatrix:
					glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, &mesh->ModelMatrix()[ 0 ][ 0 ] );
					break;
			}
		}

		std::uint8_t textureUnit = 0;
		for( const auto &tex : layer->m_textures )
		{
			glUniform1i( tex.first, textureUnit );

			tex.second.first->BindToUnit( textureUnit );
			tex.second.second->BindToUnit( textureUnit );

			textureUnit++;
		}

		for( const auto &uniform : layer->m_instanceUniforms )
		{
			uniform.second->Set( uniform.first );
		}

		vao.Draw();
	}
}
