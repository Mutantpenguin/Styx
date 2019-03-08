#pragma once

#include <string>

#include "src/helper/Types.hpp"

#include "src/renderer/GL.h"

class CTexture final
{
public:
	using ResourceIdType = std::string;

	static std::string IdToString( const ResourceIdType &id )
	{
		return( id );
	}

private:
	CTexture( const CTexture& rhs );
	CTexture & operator = ( const CTexture& rhs );

public:
	enum struct TextureType : u8
	{
		TEX_2D = 0,
		TEX_CUBE_MAP,
		TEX_2D_ARRAY
	};

	CTexture() {};
	~CTexture();

	void BindToUnit( const GLuint unit ) const;

	TextureType Type() const;
	void Type( const TextureType type );

	void Reset();

	GLuint &OpenGLID();

private:
	TextureType m_type;

	GLuint m_id;
};
