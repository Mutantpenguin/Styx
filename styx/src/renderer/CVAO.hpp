#pragma once

#include "src/renderer/GL.h"

#include "src/renderer/CBO.hpp"

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

class CVAO final
{
public:
	CVAO( const Geometry<VertexP> &geometry );
	CVAO( const Geometry<VertexPN> &geometry );
	CVAO( const Geometry<VertexPU0> &geometry );
	CVAO( const Geometry<VertexPNU0> &geometry );
	CVAO( const Geometry<VertexPNTBCU0U1U2U3> &geometry );

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
	const GLenum m_mode;

	const size_t m_indexCount;

	GLuint	GLID;

	const CBO	m_vbo;
	const CBO	m_ibo;

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
