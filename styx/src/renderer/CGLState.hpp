#pragma once

#include <array>

#include "src/renderer/GL.h"

#include "src/renderer/shader/CShaderProgramCompiler.hpp"

class CGLState final
{
public:
	static void CullFace( const bool culling, const GLenum mode );
	static void PolygonMode( const GLenum mode );

	static void Blending( const bool blending, const GLenum modeSrc, const GLenum modeDst );

	static void BlendEquation( const GLenum mode );

	static void BindTextureToUnit( const GLuint texID, const GLuint unit );

	static void BindSamplerToUnit( const GLuint samplerID, const GLuint unit );

	static void UseProgram( const GLuint program );

	static void BindVertexArray( const GLuint vao );

	static void DepthMask( const GLboolean flag );

private:
	CGLState() {};

	static bool		cullFaceEnabed;
	static GLenum	cullFaceMode;

	static GLenum	polygonMode;

	static bool		blendingEnabed;
	static GLenum	blendModeSrc;
	static GLenum	blendModeDst;

	static GLenum	blendEquation;

	static std::array< GLuint, CShaderProgramCompiler::RequiredCombinedTextureImageUnits > textureUnits;
	static std::array< GLuint, CShaderProgramCompiler::RequiredCombinedTextureImageUnits > samplerUnits;

	static GLuint usedProgram;

	static GLuint boundVertexArray;

	static GLboolean depthMaskFlag;
};
