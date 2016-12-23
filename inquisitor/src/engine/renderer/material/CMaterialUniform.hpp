#ifndef CMATERIALUNIFORM_HPP
#define CMATERIALUNIFORM_HPP

#include <glm/glm.hpp>

#include "src/engine/renderer/GL.h"

class CMaterialUniform
{
public:
	virtual void Set( const GLuint location ) const = 0;

	const std::string &Name( void ) const;

protected:
	CMaterialUniform( const std::string &name );

	const std::string m_name;
};

class CMaterialUniformFLOAT final : public CMaterialUniform
{
public:
	CMaterialUniformFLOAT( const std::string &name, const glm::float32 value );

	void Set( const GLuint location ) const override;

private:
	const glm::float32 m_value;
};

class CMaterialUniformUINT final : public CMaterialUniform
{
public:
	CMaterialUniformUINT( const std::string &name, const glm::uint value );

	void Set( const GLuint location ) const override;

private:
	const glm::uint m_value;
};


class CMaterialUniformFLOATVEC4 final : public CMaterialUniform
{
public:
	CMaterialUniformFLOATVEC4( const std::string &name, const glm::vec4 &values );

	void Set( const GLuint location ) const override;

private:
	const glm::vec4 m_values;
};

#endif // CMATERIALUNIFORM_HPP
