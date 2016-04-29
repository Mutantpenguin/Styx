#ifndef CRENDERERCAPABILITIES_HPP
#define CRENDERERCAPABILITIES_HPP

#include <set>

#include "GL.h"

class CRendererCapabilities
{
public:
	void Init( void );

	bool isSupported( const gl::GLextension extension ) const;

private:
	std::set< gl::GLextension > m_extensions;
};

#endif // CRENDERERCAPABILITIES_HPP
