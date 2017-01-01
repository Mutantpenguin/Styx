#ifndef CSOUNDLOADER_HPP
#define CSOUNDLOADER_HPP

#include "CSound.hpp"

#include "src/engine/system/CFileSystem.hpp"

class CSoundLoader
{
	friend class CSoundManager;

private:
	CSoundLoader( const CFileSystem &p_filesystem );

	std::shared_ptr< CSound > CreateSoundFromFile( const std::string &path ) const;

private:
	const CFileSystem &m_filesystem;
};

#endif // CSOUNDLOADER_HPP
