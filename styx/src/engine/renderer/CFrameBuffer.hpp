#pragma once

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
	explicit CFrameBuffer( const CSize &size );
	~CFrameBuffer();

	void Bind() const;
	void Unbind() const;

	const std::shared_ptr< const CTexture > ColorTexture() const;

	std::shared_ptr< CImage > ToImage() const;

private:
	bool isComplete();

	const CSize	m_size;
	
	GLuint	m_id;

	std::shared_ptr< CTexture > m_colorTexture;

	GLuint m_renderBufferId;

	static const GLenum attachmentColorTexture;
};
