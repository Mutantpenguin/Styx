#pragma once

#include <set>
#include <string>

#include "src/renderer/GL.h"

#include "src/core/Types.hpp"

#include "src/system/CSettings.hpp"

class COpenGlAdapter final
{
public:
	COpenGlAdapter( const CSettings &p_settings );

	GLint MaxTextureSize() const;
	GLint MaxCubeMapTextureSize() const;
	
	GLint AnisotropicLevel() const;
	
private:
	bool isSupported( const std::set<GLextension> &extensions, const GLextension extension ) const;

	GLint m_maxTextureSize;
	GLint m_maxCubeMapTextureSize;
	
	GLint m_anisotropicLevel;
};
