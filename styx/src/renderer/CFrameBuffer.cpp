#include "CFrameBuffer.hpp"

#include <glbinding-aux/Meta.h>

#include "src/logger/CLogger.hpp"

const GLenum CFrameBuffer::attachmentColorTexture = GL_COLOR_ATTACHMENT0;

CFrameBuffer::CFrameBuffer( const CSize &size ) :
	m_size { size },
	m_colorTexture { std::make_shared< CTexture >() }
{
	glCreateFramebuffers( 1, &m_id );

	std::array< GLenum, 1 > DrawBuffers { { attachmentColorTexture } };
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

		glNamedFramebufferTexture( m_id, attachmentColorTexture, colorTextureID, 0 );
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

void CFrameBuffer::Bind() const
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_id );
}

void CFrameBuffer::Unbind() const
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

const std::shared_ptr< const CTexture > CFrameBuffer::ColorTexture() const
{
	return( m_colorTexture );
}

std::shared_ptr< CImage > CFrameBuffer::ToImage() const
{
	glNamedFramebufferReadBuffer( m_id, attachmentColorTexture );

	const u32 pitch = m_size.width * 3;

	auto pixels = std::make_unique< CImage::PixelBuffer >( pitch * m_size.height );

	glReadPixels( 0, 0, m_size.width, m_size.height, GL_BGR, GL_UNSIGNED_BYTE, static_cast< void* >( pixels->data() ) );

	return( std::make_shared< CImage >( m_size, m_size, true, 24, pitch, std::move( pixels ) ) );
}

bool CFrameBuffer::isComplete()
{
	const GLenum status = glCheckNamedFramebufferStatus( m_id, GL_FRAMEBUFFER );

	if( GL_FRAMEBUFFER_COMPLETE == status )
	{
		return( true );
	}
	else
	{
		logERROR( "framebuffer is not complete: {0}", glbinding::aux::Meta::getString( status ) );
		return( false );
	}
}
