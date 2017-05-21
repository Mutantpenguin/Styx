#ifndef CSOUNDMANAGER_HPP
#define CSOUNDMANAGER_HPP

#include <unordered_map>

#include <AL/al.h>
#include <AL/alc.h>

#include <glm/glm.hpp>

#include "src/engine/system/CSettings.hpp"

#include "src/engine/sound/CSoundBuffer.hpp"
#include "src/engine/sound/CSoundBufferLoader.hpp"

class CSoundManager final
{
friend class CEngine;
friend class CEngineSystems;

public:
	void	SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up );

	[[nodiscard]] std::shared_ptr< CSoundBuffer > LoadSoundBuffer( const std::string &path );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	CSoundManager( const CSettings &settings, const CFileSystem &p_filesystem );
	~CSoundManager( void );

	CSoundManager( const CSoundManager &rhs ) = delete;
	CSoundManager& operator = ( const CSoundManager &rhs ) = delete;

	void	Update( void );

private:
	void ReloadSoundBuffers( void );

	const CFileSystem &m_filesystem;

	struct sSoundBufferFile
	{
		std::shared_ptr< CSoundBuffer >	soundBuffer;
		std::int64_t					mtime;
	};

	std::unordered_map< std::string, sSoundBufferFile > m_soundBufferFiles;

	const CSoundBufferLoader m_soundBufferloader;

	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	// TODO what does this do???
	const std::uint32_t	m_buffer_size;
};

#endif // CSOUNDMANAGER_HPP
