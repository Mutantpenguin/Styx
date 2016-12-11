#ifndef CLIBVORBISWRAPPER_HPP
#define CLIBVORBISWRAPPER_HPP

#include <vorbis/vorbisfile.h>

#include "src/engine/system/CFileSystem.hpp"

class CLibVorbisWrapper
{
public:
	static ov_callbacks &Get( const CFileSystem &p_filesystem );

private:
	CLibVorbisWrapper();
	~CLibVorbisWrapper();

	static void m_Initialize( const CFileSystem & );

	static bool m_initialized;

	static ov_callbacks m_io;
};

#endif // CLIBVORBISWRAPPER_HPP
