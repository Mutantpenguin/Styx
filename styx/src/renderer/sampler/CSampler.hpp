#pragma once

#include <memory>

#include "src/core/Types.hpp"

#include "src/renderer/GL.h"

class CSampler final
{
public:
	CSampler();
	~CSampler();

	enum class SamplerType : u8
	{
		REPEAT_2D = 0,
		BORDER_2D,
		EDGE_2D,
		REPEAT_BORDER_2D,
		REPEAT_CUBE,
		BORDER_CUBE,
		EDGE_CUBE,
		MAX
	};

	void Parametere( const GLenum pname, const GLenum param );
	void Parameteri( const GLenum pname, const GLint param );
	void Parameterf( const GLenum pname, const GLfloat param );

	void BindToUnit( const GLuint unit ) const;

protected:
	GLuint m_samplerID;
};
