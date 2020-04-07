#pragma once

#include "src/renderer/GL.h"

#include "src/renderer/CBufferObject.hpp"

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

class CVertexArrayObject final
{
public:
	CVertexArrayObject( const Geometry<VertexP> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPN> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPC> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPU0> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPCU0> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPNU0> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPNTB> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPNTBU0> &geometry, const GLenum usage );
	CVertexArrayObject( const Geometry<VertexPNTBCU0U1U2U3> &geometry, const GLenum usage );

	~CVertexArrayObject();

	template<typename T>
	void Rebuild( const Geometry<T> geometry )
	{
		m_mode = geometry.Mode;
		m_indexCount = geometry.Indices.size();
		m_vbo.Data( geometry.Vertices );
		m_ibo.Data( geometry.Indices );
	}

	void Bind() const;

	void Draw() const;

private:
	GLenum m_mode;

	size_t m_indexCount;

	GLuint	GLID;

	CBufferObject	m_vbo;
	CBufferObject	m_ibo;

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
