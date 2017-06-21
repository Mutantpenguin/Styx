#ifndef CFRAMEBUFFER_HPP
#define CFRAMEBUFFER_HPP

#include <memory>

#include "src/engine/renderer/GL.h"

#include "src/engine/renderer/texture/CTexture.hpp"

#include "src/engine/helper/CSize.hpp"

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

private:
	bool isComplete( void );

	CSize	m_size;

	std::shared_ptr< CTexture > m_colorTexture;
	std::shared_ptr< CTexture > m_depthTexture;

	GLuint	m_id;
};

#endif // CFRAMEBUFFER_HPP
