#pragma once

#include "src/renderer/GL.h"

#include "src/renderer/CVBO.hpp"

#include "src/geometry/Geometry.hpp"
#include "src/geometry/Vertex.hpp"

class CVAO final
{
public:
	CVAO( GLenum Mode, const Geometry<VertexP> &geometry );
	CVAO( GLenum Mode, const Geometry<VertexPNU0> &geometry );
	CVAO( GLenum Mode, const Geometry<VertexPNTBCU0U1U2U3> &geometry );

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
		uv0,
		uv1,
		uv2,
		uv3
	};

private:
	const GLenum m_mode; // GL_QUADS, GL_TRIS, ...

	const size_t m_vertexCount;

	GLuint	GLID;

	const CVBO	m_vbo;

	static const GLuint bindingIndexPositions	{ 0 };
	static const GLuint bindingIndexNormals		{ 1 };
	static const GLuint bindingIndexTangents	{ 2 };
	static const GLuint bindingIndexBitangents	{ 3 };
	static const GLuint bindingIndexColors		{ 4 };
	static const GLuint bindingIndexUV0			{ 5 };
	static const GLuint bindingIndexUV1			{ 6 };
	static const GLuint bindingIndexUV2			{ 7 };
	static const GLuint bindingIndexUV3			{ 8 };
};
