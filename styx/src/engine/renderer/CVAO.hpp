#pragma once

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
		position = 0,
		normal,
		texcoord,
		tangent,
		bitangent
	};

private:
	const GLenum m_mode; // GL_QUADS, GL_TRIS, ...

	GLuint	m_id;

	GLuint	m_vboId;

	const size_t m_vertexCount;

	static const GLuint bindingIndexPositions	{ 0 };
	static const GLuint bindingIndexNormals		{ 1 };
	static const GLuint bindingIndexTexcoords	{ 2 };
	static const GLuint bindingIndexTangents	{ 3 };
	static const GLuint bindingIndexBitangents	{ 4 };
};
