#ifndef CVAO_HPP
#define CVAO_HPP

#include <vector>

#include <glm/glm.hpp>

#include "src/engine/renderer/GL.h"

#include "src/engine/helper/geom/Primitives.hpp"

class CVAO final
{
public:
	CVAO( GLenum Mode, const Primitives::SPrimitive &primitive );
	~CVAO();

	void Bind( void ) const;

	void Draw( void ) const;

	enum class EAttributeLocation : GLint
	{
		vertex = 0,
		normal,
		texcoord
	};

private:
	const GLenum m_mode; // GL_QUADS, GL_TRIS, ...

	const size_t m_vertexCount;

	GLuint	m_id;

	GLuint	m_vboVertices;
	GLuint	m_vboNormals;
	GLuint	m_vboTexcoords;

	static const GLuint bindingIndexVertices	{ 0 };
	static const GLuint bindingIndexNormals		{ 1 };
	static const GLuint bindingIndexTexcoords	{ 2 };
};

#endif // CVAO_HPP
