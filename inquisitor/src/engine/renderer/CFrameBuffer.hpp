#ifndef CFRAMEBUFFER_HPP
#define CFRAMEBUFFER_HPP

#include <memory>

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/helper/CSize.hpp"

#include "src/engine/helper/image/CImage.hpp"

class CFrameBuffer
{
private:
	CFrameBuffer( const CFrameBuffer &rhs );
	CFrameBuffer & operator = (const CFrameBuffer &rhs );

public:
	CFrameBuffer( const CSize &size );
	~CFrameBuffer();

	void Bind( void ) const;
	void Unbind( void ) const;

	const std::shared_ptr< const CTexture > ColorTexture( void ) const;

	std::shared_ptr< CImage > ToImage( void ) const;

private:
	bool isComplete( void );

	const CSize	m_size;
	
	GLuint	m_id;

	std::shared_ptr< CTexture > m_colorTexture;

	GLuint m_renderBufferId;

	static const GLenum attachmentColorTexture;
};

#endif // CFRAMEBUFFER_HPP
