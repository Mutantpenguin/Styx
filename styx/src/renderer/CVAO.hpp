#pragma once

#include "src/renderer/GL.h"

#include "src/helper/geom/Primitives.hpp"

#include "src/renderer/CVBO.hpp"

class CVAO final
{
public:
	CVAO( GLenum Mode, const Primitives::SPrimitive &primitive );
	~CVAO();

	void Bind() const;

	void Draw() const;

	enum class EAttributeLocation : GLint
	{
		position = 0,
		normal,
		tangent,
		bitangent,
		color,
		texcoord0,
		texcoord1,
		texcoord2,
		texcoord3
	};

private:
	const GLenum m_mode; // GL_QUADS, GL_TRIS, ...

	GLuint	GLID;

	CVBO	m_vbo;

	static const GLuint bindingIndexPositions	{ 0 };
	static const GLuint bindingIndexNormals		{ 1 };
	static const GLuint bindingIndexTangents	{ 2 };
	static const GLuint bindingIndexBitangents	{ 3 };
	static const GLuint bindingIndexColor		{ 4 };
	static const GLuint bindingIndexTexcoords0	{ 5 };
	static const GLuint bindingIndexTexcoords1	{ 6 };
	static const GLuint bindingIndexTexcoords2	{ 7 };
	static const GLuint bindingIndexTexcoords3	{ 8 };
};
