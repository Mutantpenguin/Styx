#ifndef COPENGLADAPTER_HPP
#define COPENGLADAPTER_HPP

#include <set>
#include <exception>

#include "src/engine/renderer/GL.h"

class COpenGlAdapter final
{
public:
	COpenGlAdapter();
	~COpenGlAdapter();

	GLint PreferredInternalTextureFormat2D( void ) const;
	GLint PreferredInternalTextureFormatCube( void ) const;
	GLint PreferredInternalTextureFormat2DArray( void ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	bool isSupported( const std::set< GLextension > &extensions, const GLextension extension ) const;

	GLint m_preferredInternalTextureFormat2D		{ static_cast< GLint >( GL_RGBA8 ) };
	GLint m_preferredInternalTextureFormatCube		{ static_cast< GLint >( GL_RGBA8 ) };
	GLint m_preferredInternalTextureFormat2DArray 	{ static_cast< GLint >( GL_RGBA8 ) };
};

#endif // COPENGLADAPTER_HPP
