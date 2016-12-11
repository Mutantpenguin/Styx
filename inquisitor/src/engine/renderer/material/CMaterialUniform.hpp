#ifndef CMATERIALUNIFORM_HPP
#define CMATERIALUNIFORM_HPP

#include <glm/glm.hpp>

#include "../GL.h"

class CMaterialUniform
{
public:
	virtual void Set( const GLuint location ) const = 0;
};


class CMaterialUniformUINT final : public CMaterialUniform
{
public:
	CMaterialUniformUINT( const glm::uint value );

	void Set( const GLuint location ) const override;

private:
	const glm::uint m_value;
};


class CMaterialUniformFLOATVEC4 final : public CMaterialUniform
{
public:
	CMaterialUniformFLOATVEC4( const glm::vec4 &values );

	void Set( const GLuint location ) const override;

private:
	const glm::vec4 m_values;
};

#endif // CMATERIALUNIFORM_HPP
