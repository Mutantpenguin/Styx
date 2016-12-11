#ifndef CFREEIMAGEWRAPPER_HPP
#define CFREEIMAGEWRAPPER_HPP

#include <FreeImagePlus.h>

#include "src/engine/system/CFileSystem.hpp"

class CFreeImageWrapper final
{
public:
	static FreeImageIO &Get( const CFileSystem &p_filesystem );

private:
	CFreeImageWrapper();
	~CFreeImageWrapper();

	static void Initialize( const CFileSystem & );

	static bool m_initialized;

	static FreeImageIO m_io;
};

#endif // CFREEIMAGEWRAPPER_HPP
