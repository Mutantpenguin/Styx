#include "COpenGlAdapter.hpp"

#include <glbinding/Binding.h>
#include <glbinding/Meta.h>
#include <glbinding/ContextInfo.h>
#include <glbinding/Version.h>

#include "src/engine/renderer/shader/CShaderManager.hpp"

#include "src/engine/logger/CLogger.hpp"

COpenGlAdapter::COpenGlAdapter()
{
	glbinding::Binding::initialize();

	const auto supportedOpenGLExtensions = glbinding::ContextInfo::extensions();

	logINFO( "" );
	logINFO( "OpenGL" );
	logINFO( "\tVersion:  {0}",          glbinding::ContextInfo::version().toString() );
	logINFO( "\tVendor:   {0}",          glbinding::ContextInfo::vendor() );
	logINFO( "\tRenderer: {0}",          glbinding::ContextInfo::renderer() );
	logINFO( "\tRevision: {0} (gl.xml)", glbinding::Meta::glRevision() );
	logINFO( "GLSL" );
	logINFO( "\tVersion:  {0}",          glGetString( GL_SHADING_LANGUAGE_VERSION ) );
	logINFO( "" );

	#ifdef INQ_DEBUG
		if( isSupported( supportedOpenGLExtensions, GLextension::GL_KHR_debug )
			||
			isSupported( supportedOpenGLExtensions, GLextension::GL_ARB_debug_output ) )
		{
			logINFO( "OpenGL debug output enabled" );

			glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );

			glDebugMessageCallback(	[]( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, const GLchar* message, const void* )
									{
										const e_loglevel loglvl = ( GL_DEBUG_SEVERITY_HIGH == severity ) ? e_loglevel::eERROR : e_loglevel::eWARNING;

										LOG( loglvl, "OpenGL ERROR" );
										LOG( loglvl, "\tSource   : {0}", glbinding::Meta::getString( source ) );
										LOG( loglvl, "\tType     : {0}", glbinding::Meta::getString( type ) );
										LOG( loglvl, "\tID       : {0}", id );
										LOG( loglvl, "\tSeverity : {0}", glbinding::Meta::getString( severity ) );
										LOG( loglvl, "\tMessage  : {0}", message );
									}, nullptr );
		}
		else
		{
			logWARNING( "neither {0} nor {1} are available", glbinding::Meta::getString( GLextension::GL_KHR_debug ), glbinding::Meta::getString( GLextension::GL_ARB_debug_output ) );
		}
	#endif


	GLint maxCombinedTextureImageUnits { 0 };
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits );
	if( maxCombinedTextureImageUnits < CShaderManager::requiredCombinedTextureImageUnits )
	{
		logERROR( "not enough combined texture image units: {0} found but {1} needed", maxCombinedTextureImageUnits, CShaderManager::requiredCombinedTextureImageUnits );
		throw Exception();
	}
	logDEBUG( "{0} is {1}", glbinding::Meta::getString( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS ), maxCombinedTextureImageUnits );


	logINFO( "required OpenGL extensions:" );
	const auto requiredOpenGLExtensions = {	GLextension::GL_EXT_texture_filter_anisotropic,
											// TODO not needed anymore when we can switch to a 4.2 core context (or higher)
											GLextension::GL_ARB_shading_language_420pack,
											GLextension::GL_ARB_texture_storage,
											// TODO not needed anymore when we can switch to a 4.3 core context (or higher)
											GLextension::GL_ARB_program_interface_query,
											// TODO not needed anymore when we can switch to a 4.5 core context (or higher)
											GLextension::GL_ARB_direct_state_access };

	bool requiredExtensionsMissing = false;
	for( const auto &extension : requiredOpenGLExtensions )
	{
		if( !isSupported( supportedOpenGLExtensions, extension ) )
		{
			logERROR( "\t{0} is MISSING", glbinding::Meta::getString( extension ) );
			requiredExtensionsMissing = true;
		}
		else
		{
			logINFO( "\t{0} is available", glbinding::Meta::getString( extension ) );
		}
	}

	if( requiredExtensionsMissing )
	{
		throw Exception();
	}


	const bool supports_GL_NVX_gpu_memory_info = isSupported( supportedOpenGLExtensions, GLextension::GL_NVX_gpu_memory_info );
	const bool supports_GL_ATI_meminfo         = isSupported( supportedOpenGLExtensions, GLextension::GL_ATI_meminfo );

	logINFO( "video memory:" );
	if( !supports_GL_NVX_gpu_memory_info && !supports_GL_ATI_meminfo )
	{
		logINFO( "\tno information available" );
		logDEBUG( "\tneither {0} nor {1} are supported", glbinding::Meta::getString( GLextension::GL_NVX_gpu_memory_info ), glbinding::Meta::getString( GLextension::GL_ATI_meminfo ) );
	}
	else
	{
		if( supports_GL_NVX_gpu_memory_info )
		{
			logDEBUG( "\t{0} is supported", glbinding::Meta::getString( GLextension::GL_NVX_gpu_memory_info ) );

			GLint dedicatedMemKb = 0;
			glGetIntegerv( GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicatedMemKb );

			GLint totalAvailableMemKb = 0;
			glGetIntegerv( GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalAvailableMemKb );

			GLint currentlyAvailableMemKb = 0;
			glGetIntegerv( GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currentlyAvailableMemKb );

			logINFO( "\ttotal dedicated:     {0} MiB", dedicatedMemKb / 1024 );
			logINFO( "\ttotal available:     {0} MiB", totalAvailableMemKb / 1024 );
			logINFO( "\tcurrently available: {0} MiB", currentlyAvailableMemKb / 1024 );
		}

		if( supports_GL_ATI_meminfo )
		{
			logDEBUG( "\t{0} is supported", glbinding::Meta::getString( GLextension::GL_ATI_meminfo ) );

			GLint vboFreeMemKb = 0;
			glGetIntegerv( GL_VBO_FREE_MEMORY_ATI, &vboFreeMemKb );

			GLint textureFreeMemKb = 0;
			glGetIntegerv( GL_TEXTURE_FREE_MEMORY_ATI, &textureFreeMemKb );

			GLint renderbufferFreeMemKb = 0;
			glGetIntegerv( GL_RENDERBUFFER_FREE_MEMORY_ATI, &renderbufferFreeMemKb );

			logINFO( "\tfree for VBOs:           {0} MiB", vboFreeMemKb / 1024 );
			logINFO( "\tfree for textures:       {0} MiB", textureFreeMemKb / 1024 );
			logINFO( "\tfree for render buffers: {0} MiB", renderbufferFreeMemKb / 1024 );
		}
	}


	if( isSupported( supportedOpenGLExtensions, GLextension::GL_ARB_internalformat_query2 ) )
	{
		logINFO( "using {0} for internal texture formats", glbinding::Meta::getString( GLextension::GL_ARB_internalformat_query2 ) );

		glGetInternalformativ( GL_TEXTURE_2D,		GL_RGBA8, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormat2D );
		glGetInternalformativ( GL_TEXTURE_CUBE_MAP,	GL_RGBA8, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormatCube );
		glGetInternalformativ( GL_TEXTURE_2D_ARRAY,	GL_RGBA8, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormat2DArray );
	}
}

COpenGlAdapter::~COpenGlAdapter()
{
}

GLint COpenGlAdapter::PreferredInternalTextureFormat2D( void ) const
{
	return( m_preferredInternalTextureFormat2D );
}

GLint COpenGlAdapter::PreferredInternalTextureFormatCube( void ) const
{
	return( m_preferredInternalTextureFormatCube );
}

GLint COpenGlAdapter::PreferredInternalTextureFormat2DArray( void ) const
{
	return( m_preferredInternalTextureFormat2DArray );
}

bool COpenGlAdapter::isSupported( const std::set< GLextension > &extensions, const GLextension extension ) const
{
	if( extensions.find( extension ) != std::end( extensions ) )
	{
		return( true );
	}
	else
	{
		return( false );
	}
}
