#ifndef CVAO_HPP
#define CVAO_HPP

#include <vector>

#include <glm/glm.hpp>

#include "GL.h"

#include "../helper/geom/Primitives.hpp"

class CVAO final
{
public:
	CVAO( GLenum Mode, const Primitives::SPrimitive &primitive );
	~CVAO();

	void Bind( void ) const;

	void Draw( void ) const;

	constexpr static const GLint attributeLocationVertex	{ 0 };
	constexpr static const GLint attributeLocationNormal	{ 1 };
	constexpr static const GLint attributeLocationTexcoord	{ 2 };

private:
	const GLenum m_mode; // GL_QUADS, GL_TRIS, ...

	const size_t m_vertexCount;

	GLuint	m_vao;

	GLuint	m_vboVertices;
	GLuint	m_vboNormals;
	GLuint	m_vboTexcoords;

	static const GLuint bindingIndexVertices	{ 0 };
	static const GLuint bindingIndexNormals		{ 1 };
	static const GLuint bindingIndexTexcoords	{ 2 };
};

#endif // CVAO_HPP
