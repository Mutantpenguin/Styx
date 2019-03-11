#pragma once

#include <string>

#include "src/helper/Types.hpp"

#include "src/renderer/GL.h"

class CShader final
{
public:
	using ResourceIdType = std::string;

	static std::string IdToString( const ResourceIdType &id )
	{
		return( id );
	}

private:
	CShader( const CShader& rhs );
	CShader & operator = ( const CShader& rhs );

public:
	enum struct EType : u8
	{
		VERTEX = 0,
		FRAGMENT
	};

	CShader() {};
	~CShader();

	void Reset();

	GLuint GLID;
};