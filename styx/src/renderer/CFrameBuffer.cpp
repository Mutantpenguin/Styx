#include "CFrameBuffer.hpp"

#include <glbinding-aux/Meta.h>

#include "src/logger/CLogger.hpp"

#include "src/core/StyxException.hpp"

const GLenum CFrameBuffer::attachmentColorTexture = GL_COLOR_ATTACHMENT0;

CFrameBuffer::CFrameBuffer( const CSize &size ) :
	Size { size },
	m_colorTexture { std::make_shared<CTexture>() }
{
	glCreateFramebuffers( 1, &GLID );

	const std::array<GLenum, 1> DrawBuffers { { attachmentColorTexture } };
	glNamedFramebufferDrawBuffers( GLID, DrawBuffers.size(), DrawBuffers.data() );

	{
		m_colorTexture->Target = GL_TEXTURE_2D;
		glCreateTextures( m_colorTexture->Target, 1, &m_colorTexture->GLID );

		glTextureParameteri( m_colorTexture->GLID, GL_TEXTURE_BASE_LEVEL, 0 );
		glTextureParameteri( m_colorTexture->GLID, GL_TEXTURE_MAX_LEVEL, 1 );

		glTextureStorage2D( m_colorTexture->GLID,
							1,
							GL_RGBA8,
							size.width,
							size.height );

		glNamedFramebufferTexture( GLID, attachmentColorTexture, m_colorTexture->GLID, 0 );
	}

	glCreateRenderbuffers( 1, &m_renderBufferId );
	glNamedRenderbufferStorage( m_renderBufferId, GL_DEPTH24_STENCIL8, size.width, size.height );
	glNamedFramebufferRenderbuffer( GLID, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId );

	const GLenum status = glCheckNamedFramebufferStatus( GLID, GL_FRAMEBUFFER );

	if( GL_FRAMEBUFFER_COMPLETE != status )
	{
		THROW_STYX_EXCEPTION( "framebuffer is not complete: {0}", glbinding::aux::Meta::getString( status ) )
	}
}

CFrameBuffer::~CFrameBuffer()
{
	glDeleteRenderbuffers( 1, &m_renderBufferId );

	glDeleteFramebuffers( 1, &GLID );
}

void CFrameBuffer::Bind() const
{
	glBindFramebuffer( GL_FRAMEBUFFER, GLID );
}

void CFrameBuffer::Unbind() const
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void CFrameBuffer::Clear( const CColor &color ) const
{
	const std::array<f16, 4> colorArray = { color.r(), color.g(), color.b(), color.a() };
	const f16 depthValue = 1.0f;
	
	glClearNamedFramebufferfv( GLID, GL_COLOR, 0, colorArray.data() );
	glClearNamedFramebufferfv( GLID, GL_DEPTH, 0, &depthValue );
}

const std::shared_ptr<const CTexture> CFrameBuffer::ColorTexture() const
{
	return( m_colorTexture );
}

CImage CFrameBuffer::ToImage() const
{
	glNamedFramebufferReadBuffer( GLID, attachmentColorTexture );

	const u32 pitch = Size.width * 3;

	auto pixels = std::make_unique<CImage::PixelBuffer>( pitch * Size.height );

	glReadPixels( 0, 0, Size.width, Size.height, GL_RGB, GL_UNSIGNED_BYTE, static_cast<void*>( pixels->data() ) );

	return( CImage( Size, 24, pitch, std::move( pixels ) ) );
}
