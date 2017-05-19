#ifndef CSOUNDMANAGER_HPP
#define CSOUNDMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include <glm/glm.hpp>

#include "src/engine/system/CSettings.hpp"

#include "src/engine/sound/CSound.hpp"
#include "src/engine/sound/CSoundLoader.hpp"

class CSoundManager final
{
friend class CEngine;
friend class CEngineSystems;

public:
	void	SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up );

	// TODO - this is just for testing sound
	[[nodiscard]] std::shared_ptr< CSound > Load( const std::string &path ) const;
	// TODO - this is just temporary to test sound-output
	void	Play( const std::shared_ptr< const CSound > &sound ) const;

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
	const CSoundLoader m_soundloader;

	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	const std::uint32_t	m_buffer_size;
};

#endif // CSOUNDMANAGER_HPP
