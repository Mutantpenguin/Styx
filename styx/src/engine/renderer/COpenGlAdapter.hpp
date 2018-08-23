#ifndef COPENGLADAPTER_HPP
#define COPENGLADAPTER_HPP

#include <set>
#include <exception>

#include "src/engine/renderer/GL.h"

class COpenGlAdapter final
{
public:
	COpenGlAdapter();

	GLint MaxTextureSize( void ) const;
	GLint MaxCubeMapTextureSize( void ) const;

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

	GLint m_maxTextureSize;
	GLint m_maxCubeMapTextureSize;

	GLint m_preferredInternalTextureFormat2D;
	GLint m_preferredInternalTextureFormatCube;
	GLint m_preferredInternalTextureFormat2DArray;
};

#endif // COPENGLADAPTER_HPP
