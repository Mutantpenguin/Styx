#ifndef CSAMPLER_HPP
#define CSAMPLER_HPP

#include <memory>

#include <cstdint>

#include "src/engine/renderer/GL.h"

class CSampler final
{
public:
	CSampler();
	~CSampler();

	enum class Type : std::uint8_t
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

	void BindToUnit( const GLuint unit );

protected:
	GLuint m_samplerID;
};

#endif // CSAMPLER_HPP
