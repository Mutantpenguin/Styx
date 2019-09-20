#include "CSampler.hpp"

#include "src/renderer/CGLState.hpp"

CSampler::CSampler()
{
	glGenSamplers( 1, &m_samplerID );
}

CSampler::~CSampler()
{
	glDeleteSamplers( 1, &m_samplerID );
}

void CSampler::Parametere( const GLenum pname, const GLenum param )
{
	glSamplerParameteri( m_samplerID, pname, static_cast<GLint>( param ) );
}

void CSampler::Parameteri( const GLenum pname, const GLint param )
{
	glSamplerParameteri( m_samplerID, pname, param );
}

void CSampler::Parameterf( const GLenum pname, const GLfloat param )
{
	glSamplerParameterf( m_samplerID, pname, param );
}

void CSampler::BindToUnit( const GLuint unit ) const
{
	CGLState::BindSamplerToUnit( m_samplerID, unit );
}
