#ifndef CINSTANCEUNIFORM_HPP
#define CINSTANCEUNIFORM_HPP

#include <glm/glm.hpp>

#include "../GL.h"

class CInstanceUniform
{
public:
	virtual void Set( const GLuint location ) = 0;
};


class CInstanceUniformUINT final : public CInstanceUniform
{
public:
	CInstanceUniformUINT( const glm::uint value );

	void Set( const GLuint location ) override;

private:
	glm::uint m_value;
};


class CInstanceUniformFLOATVEC4 final : public CInstanceUniform
{
public:
	CInstanceUniformFLOATVEC4( const glm::vec4 &values );

	void Set( const GLuint location ) override;

private:
	glm::vec4 m_values;
};

#endif // CINSTANCEUNIFORM_HPP
