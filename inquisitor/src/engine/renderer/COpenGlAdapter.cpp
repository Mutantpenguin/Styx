#include "COpenGlAdapter.hpp"

#include <glbinding/Binding.h>
#include <glbinding/Meta.h>
#include <glbinding/ContextInfo.h>
#include <glbinding/Version.h>

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/shader/CShaderManager.hpp"

#include "src/engine/logger/CLogger.hpp"

COpenGlAdapter::COpenGlAdapter()
{
	glbinding::Binding::initialize();

	logINFO( "OpenGL" );
	logINFO( "\tVersion:  {0}",          glbinding::ContextInfo::version().toString() );
	logINFO( "\tVendor:   {0}",          glbinding::ContextInfo::vendor() );
	logINFO( "\tRenderer: {0}",          glbinding::ContextInfo::renderer() );
	logINFO( "\tRevision: {0} (gl.xml)", glbinding::Meta::glRevision() );
	logINFO( "GLSL" );
	logINFO( "\tVersion:  {0}",          glGetString( GL_SHADING_LANGUAGE_VERSION ) );

	GLint maxCombinedTextureImageUnits { 0 };
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits );
	if( maxCombinedTextureImageUnits < CShaderManager::requiredCombinedTextureImageUnits )
	{
		logERROR( "not enough combined texture image units: {0} found but {1} needed", maxCombinedTextureImageUnits, CShaderManager::requiredCombinedTextureImageUnits );
		throw Exception();
	}
	logDEBUG( "{0} is {1}", glbinding::Meta::getString( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS ), maxCombinedTextureImageUnits );
}

COpenGlAdapter::~COpenGlAdapter()
{
}
