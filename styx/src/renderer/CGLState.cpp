#include "CGLState.hpp"

bool	CGLState::cullFaceEnabed	{ false };
GLenum	CGLState::cullFaceMode		{ GL_NONE };

GLenum	CGLState::polygonMode	{ GL_FILL };

bool	CGLState::blendingEnabed	{ false };
GLenum	CGLState::blendModeSrc		{ GL_NONE };
GLenum	CGLState::blendModeDst		{ GL_NONE };

GLenum	CGLState::blendEquation		{ GL_NONE };

std::array< GLuint, CShaderProgramCompiler::RequiredCombinedTextureImageUnits > CGLState::textureUnits;
std::array< GLuint, CShaderProgramCompiler::RequiredCombinedTextureImageUnits > CGLState::samplerUnits;

GLuint CGLState::usedProgram;

GLuint CGLState::boundVertexArray;

void CGLState::CullFace( const bool culling, const GLenum mode )
{
	if( cullFaceEnabed != culling )
	{
		cullFaceEnabed = culling;

		if( culling )
		{
			glEnable( GL_CULL_FACE );
		}
		else
		{
			glDisable( GL_CULL_FACE );
		}
	}

	if( culling && ( cullFaceMode != mode ) )
	{
		cullFaceMode = mode;
		glCullFace( mode );
	}
}

void CGLState::PolygonMode( const GLenum mode )
{
	if( mode != polygonMode )
	{
		polygonMode = mode;
		glPolygonMode( GL_FRONT_AND_BACK, mode );
	}
}

void CGLState::Blending( const bool blending, const GLenum modeSrc, const GLenum modeDst )
{
	if( blendingEnabed != blending )
	{
		blendingEnabed = blending;

		if( blending )
		{
			glEnable( GL_BLEND );
		}
		else
		{
			glDisable( GL_BLEND );
		}
	}

	if( blending && (	( blendModeSrc != modeSrc )
						||
						( blendModeDst != modeDst ) ) )
	{
			blendModeSrc = modeSrc;
			blendModeDst = modeDst;
			glBlendFunc( modeSrc, modeDst );
	}
}

void CGLState::BlendEquation( const GLenum mode )
{
	if( mode != blendEquation )
	{
		blendEquation = mode;
		glBlendEquation( mode );
	}
}

void CGLState::BindTextureToUnit( const GLuint texID, const GLuint unit )
{
	if( texID != textureUnits[ unit ] )
	{
		textureUnits[ unit ] = texID;
		glBindTextureUnit( unit, texID );
	}
}

void CGLState::BindSamplerToUnit( const GLuint samplerID, const GLuint unit )
{
	if( samplerID != samplerUnits[ unit ] )
	{
		samplerUnits[ unit ] = samplerID;
		glBindSampler( unit, samplerID );
	}
}

void CGLState::UseProgram( const GLuint program )
{
	if( program != usedProgram )
	{
		usedProgram = program;
		glUseProgram( program );
	}
}

void CGLState::BindVertexArray( const GLuint vao )
{
	if( vao != boundVertexArray )
	{
		boundVertexArray = vao;
		glBindVertexArray( vao );
	}
}
