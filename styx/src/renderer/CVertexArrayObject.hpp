#pragma once

#include "src/renderer/GL.h"

#include "src/renderer/CBufferObject.hpp"

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

class CVertexArrayObject final
{
public:
	CVertexArrayObject( const Geometry<VertexP> &geometry );
	CVertexArrayObject( const Geometry<VertexPN> &geometry );
	CVertexArrayObject( const Geometry<VertexPU0> &geometry );
	CVertexArrayObject( const Geometry<VertexPNU0> &geometry );
	CVertexArrayObject( const Geometry<VertexPNTB> &geometry );
	CVertexArrayObject( const Geometry<VertexPNTBU0> &geometry );
	CVertexArrayObject( const Geometry<VertexPNTBCU0U1U2U3> &geometry );

	~CVertexArrayObject();

	void Bind() const;

	void Draw() const;

private:
	const GLenum m_mode;

	const size_t m_indexCount;

	GLuint	GLID;

	const CBufferObject	m_vbo;
	const CBufferObject	m_ibo;

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
