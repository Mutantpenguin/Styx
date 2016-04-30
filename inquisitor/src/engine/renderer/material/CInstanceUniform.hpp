#ifndef CINSTANCEUNIFORM_HPP
#define CINSTANCEUNIFORM_HPP

#include <glm/glm.hpp>

#include "../GL.h"

class CInstanceUniform
{
public:
	CInstanceUniform( const GLuint uniformLocation );

	virtual void Set( void ) = 0;

protected:
	const GLuint m_uniformLocation;
};

class CInstanceUniformUINT final : public CInstanceUniform
{
public:
	CInstanceUniformUINT( const GLuint uniformLocation, const glm::uint value );

	void Set( void );

private:
	glm::uint m_value;
};

#endif // CINSTANCEUNIFORM_HPP
