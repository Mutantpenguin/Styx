#include "CFrameBuffer.hpp"

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

CFrameBuffer::CFrameBuffer( const CSize &size ) :
	m_size { size },
	m_colorTexture { std::make_shared< CTexture >() }
{
	glCreateFramebuffers( 1, &m_id );

	std::array< GLenum, 1 > DrawBuffers { GL_COLOR_ATTACHMENT0 };
	glFramebufferDrawBuffersEXT( m_id, DrawBuffers.size(), DrawBuffers.data() );

	{
		auto &colorTextureID = m_colorTexture->OpenGLID();

		m_colorTexture->Type( CTexture::TextureType::TEX_2D );
		glCreateTextures( GL_TEXTURE_2D, 1, &colorTextureID );

		glTextureParameteri( colorTextureID, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( colorTextureID, GL_TEXTURE_MAX_LEVEL, 1 );

		glTextureStorage2D(	colorTextureID,
							1,
							GL_RGBA8,
							size.width,
							size.height );

		glNamedFramebufferTexture( m_id, GL_COLOR_ATTACHMENT0, colorTextureID, 0 );
	}

	glCreateRenderbuffers( 1, &m_renderBufferId );
	glNamedRenderbufferStorage( m_renderBufferId, GL_DEPTH24_STENCIL8, size.width, size.height );
	glNamedFramebufferRenderbuffer( m_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId );

	if( !isComplete() )
	{
		throw std::exception();
	}
}

CFrameBuffer::~CFrameBuffer()
{
	glDeleteRenderbuffers( 1, &m_renderBufferId );

	glDeleteFramebuffers( 1, &m_id );
}

void CFrameBuffer::Bind( void ) const
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_id );
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
	const GLenum status = glCheckNamedFramebufferStatus( m_id, GL_FRAMEBUFFER );

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
