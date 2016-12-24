#ifndef CRENDERERCAPABILITIES_HPP
#define CRENDERERCAPABILITIES_HPP

#include <set>

#include "GL.h"

class CRendererCapabilities final
{
public:
	CRendererCapabilities( void );

	bool isSupported( const gl::GLextension extension ) const;

private:
	const std::set< gl::GLextension > m_extensions;
};

#endif // CRENDERERCAPABILITIES_HPP
