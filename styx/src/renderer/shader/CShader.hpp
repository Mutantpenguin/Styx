#pragma once

#include <string>

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
	CShader() {};
	~CShader();

	GLuint GLID;
};