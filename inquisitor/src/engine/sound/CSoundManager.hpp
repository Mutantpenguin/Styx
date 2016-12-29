#ifndef CSOUNDMANAGER_HPP
#define CSOUNDMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include "src/engine/system/CSettings.hpp"

#include "src/engine/renderer/camera/CCamera.hpp"

#include "CSound.hpp"

class CSoundManager final
{
friend class CEngine;

public:
	void	SetListener( const std::shared_ptr< const CCamera > &camera );

	// TODO - this is just for testing sound
	static void	Play( const std::shared_ptr< const CSound > &sound );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	CSoundManager( const CSettings &settings );
	~CSoundManager( void );

	void	Update( void );

private:
	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	const std::uint32_t	m_buffer_size;
};

#endif // CSOUNDMANAGER_HPP
