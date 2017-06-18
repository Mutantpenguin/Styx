#include "CFrameBuffer.hpp"

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

CFrameBuffer::CFrameBuffer( const CSize &size ) :
	m_size { size },
	m_colorTexture { std::make_shared< CTexture >() },
	m_depthTexture { std::make_shared< CTexture >() }
{
	glCreateFramebuffers( 1, &m_frameBufferID );

	m_colorTexture->m_type = CTexture::type::TEX_2D;
	glCreateTextures( GL_TEXTURE_2D, 1, &m_colorTexture->m_textureID );

	glTextureParameteri( m_colorTexture->m_textureID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_colorTexture->m_textureID, GL_TEXTURE_MAX_LEVEL, 1 );

	glTextureStorage2D(	m_colorTexture->m_textureID,
						1,
						GL_RGBA8,
						size.width,
						size.height );

	glTextureSubImage2D(	m_colorTexture->m_textureID,
							0, // level
							0, // xoffset
							0, // yoffset
							size.width,
							size.height,
							GL_RGB,
							GL_UNSIGNED_BYTE,
							nullptr );

	glNamedFramebufferTexture( m_frameBufferID, GL_COLOR_ATTACHMENT0, m_colorTexture->m_textureID, 0 );

	m_depthTexture->m_type = CTexture::type::TEX_2D;
	glCreateTextures( GL_TEXTURE_2D, 1, &m_depthTexture->m_textureID );

	glTextureParameteri( m_depthTexture->m_textureID, GL_TEXTURE_BASE_LEVEL, 0 );
	glTextureParameteri( m_depthTexture->m_textureID, GL_TEXTURE_MAX_LEVEL, 1 );

	glTextureStorage2D(	m_depthTexture->m_textureID,
						1,
						GL_DEPTH_COMPONENT32F,
						size.width,
						size.height );

	glTextureSubImage2D(	m_colorTexture->m_textureID,
							0, // level
							0, // xoffset
							0, // yoffset
							size.width,
							size.height,
							GL_DEPTH_COMPONENT,
							GL_UNSIGNED_BYTE,
							nullptr );

	glNamedFramebufferTexture( m_frameBufferID, GL_DEPTH_ATTACHMENT, m_depthTexture->m_textureID, 0 );

	if( !isComplete() )
	{
		throw std::exception();
	}
}

CFrameBuffer::~CFrameBuffer()
{
	glDeleteFramebuffers( 1, &m_frameBufferID );
}

void CFrameBuffer::Bind( void ) const
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_frameBufferID );
}

void CFrameBuffer::Unbind( void ) const
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

const std::shared_ptr< const CTexture > CFrameBuffer::ColorTexture( void ) const
{
	return( m_colorTexture );
}

bool CFrameBuffer::isComplete( void )
{
	const GLenum status = glCheckNamedFramebufferStatus( m_frameBufferID, GL_FRAMEBUFFER );

	if( GL_FRAMEBUFFER_COMPLETE == status )
	{
		return( true );
	}
	else
	{
		logERROR( "framebuffer is not complete: {0}", glbinding::Meta::getString( status ) );
		return( false );
	}
}
