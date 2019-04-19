#include "COpenGlAdapter.hpp"

#include <glbinding/Binding.h>
#include <glbinding-aux/Meta.h>
#include <glbinding-aux/ContextInfo.h>
#include <glbinding/Version.h>

#include "src/renderer/shader/CShaderProgramCompiler.hpp"

#include "src/core/StyxException.hpp"

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/logger/CLogger.hpp"

COpenGlAdapter::COpenGlAdapter()
{
	glbinding::Binding::initialize( []( const char *name ) {
        return reinterpret_cast< glbinding::ProcAddress >( SDL_GL_GetProcAddress( name ) );
    } );

	const auto supportedOpenGLExtensions = glbinding::aux::ContextInfo::extensions();

	logINFO( "" );
	logINFO( "OpenGL" );
	logINFO( "\tVersion:  {0}",          glbinding::aux::ContextInfo::version().toString() );
	logINFO( "\tVendor:   {0}",          glbinding::aux::ContextInfo::vendor() );
	logINFO( "\tRenderer: {0}",          glbinding::aux::ContextInfo::renderer() );
	logINFO( "\tRevision: {0} (gl.xml)", glbinding::aux::Meta::glRevision() );
	logINFO( "GLSL" );
	logINFO( "\tVersion:  {0}",          glGetString( GL_SHADING_LANGUAGE_VERSION ) );
	logINFO( "" );

	#ifdef STYX_DEBUG
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
										LOG( loglvl, "\tSource   : {0}", glbinding::aux::Meta::getString( source ) );
										LOG( loglvl, "\tType     : {0}", glbinding::aux::Meta::getString( type ) );
										LOG( loglvl, "\tID       : {0}", id );
										LOG( loglvl, "\tSeverity : {0}", glbinding::aux::Meta::getString( severity ) );
										LOG( loglvl, "\tMessage  : {0}", message );
									}, nullptr );
		}
		else
		{
			logWARNING( "since neither {0} nor {1} are available, OpenGL debug output is disabled", glbinding::aux::Meta::getString( GLextension::GL_KHR_debug ), glbinding::aux::Meta::getString( GLextension::GL_ARB_debug_output ) );
		}
	#endif


	GLint maxCombinedTextureImageUnits { 0 };
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits );
	if( maxCombinedTextureImageUnits < CShaderProgramCompiler::RequiredCombinedTextureImageUnits )
	{
		THROW_STYX_EXCEPTION( "not enough combined texture image units: {0} found but {1} needed", maxCombinedTextureImageUnits, CShaderProgramCompiler::RequiredCombinedTextureImageUnits )
	}
	logDEBUG( "{0} is {1}", glbinding::aux::Meta::getString( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS ), maxCombinedTextureImageUnits );


	logINFO( "required OpenGL extensions:" );
	const auto requiredOpenGLExtensions = {	GLextension::GL_EXT_texture_filter_anisotropic,
											// TODO not needed anymore when we can switch to a 4.5 core context (or higher)
											GLextension::GL_ARB_direct_state_access };

	bool requiredExtensionsMissing = false;
	for( const auto &extension : requiredOpenGLExtensions )
	{
		if( !isSupported( supportedOpenGLExtensions, extension ) )
		{
			logERROR( "\t{0} is MISSING", glbinding::aux::Meta::getString( extension ) );
			requiredExtensionsMissing = true;
		}
		else
		{
			logINFO( "\t{0} is available", glbinding::aux::Meta::getString( extension ) );
		}
	}

	if( requiredExtensionsMissing )
	{
		THROW_STYX_EXCEPTION( "at least one required extension is missing" );
	}

	const bool supports_GL_NVX_gpu_memory_info = isSupported( supportedOpenGLExtensions, GLextension::GL_NVX_gpu_memory_info );
	const bool supports_GL_ATI_meminfo         = isSupported( supportedOpenGLExtensions, GLextension::GL_ATI_meminfo );

	logINFO( "video memory:" );
	if( !supports_GL_NVX_gpu_memory_info && !supports_GL_ATI_meminfo )
	{
		logINFO( "\tno information available" );
		logDEBUG( "\tneither {0} nor {1} are supported", glbinding::aux::Meta::getString( GLextension::GL_NVX_gpu_memory_info ), glbinding::aux::Meta::getString( GLextension::GL_ATI_meminfo ) );
	}
	else
	{
		if( supports_GL_NVX_gpu_memory_info )
		{
			logDEBUG( "\t{0} is supported", glbinding::aux::Meta::getString( GLextension::GL_NVX_gpu_memory_info ) );

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
			logDEBUG( "\t{0} is supported", glbinding::aux::Meta::getString( GLextension::GL_ATI_meminfo ) );

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

	// fetch the preferred internal texture formats
	glGetInternalformativ( GL_TEXTURE_2D,		GL_RGBA8, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormat2D );
	glGetInternalformativ( GL_TEXTURE_CUBE_MAP,	GL_RGBA8, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormatCube );
	glGetInternalformativ( GL_TEXTURE_2D_ARRAY,	GL_RGBA8, GL_INTERNALFORMAT_PREFERRED, 1, &m_preferredInternalTextureFormat2DArray );

	// fetch the maximal texture size
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_maxTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::aux::Meta::getString( GL_MAX_TEXTURE_SIZE ), m_maxTextureSize );

	// fetch the maximal cubemap texture size
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_maxCubeMapTextureSize );
	logDEBUG( "{0} is '{1}'", glbinding::aux::Meta::getString( GL_MAX_CUBE_MAP_TEXTURE_SIZE ), m_maxCubeMapTextureSize );
}

GLint COpenGlAdapter::MaxTextureSize() const
{
	return( m_maxTextureSize );
}

GLint COpenGlAdapter::MaxCubeMapTextureSize() const
{
	return( m_maxCubeMapTextureSize );
}

GLint COpenGlAdapter::PreferredInternalTextureFormat2D() const
{
	return( m_preferredInternalTextureFormat2D );
}

GLint COpenGlAdapter::PreferredInternalTextureFormatCube() const
{
	return( m_preferredInternalTextureFormatCube );
}

GLint COpenGlAdapter::PreferredInternalTextureFormat2DArray() const
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
