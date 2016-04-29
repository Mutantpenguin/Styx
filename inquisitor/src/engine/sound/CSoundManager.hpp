#ifndef CSOUNDMANAGER_HPP
#define CSOUNDMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include "../system/CSettings.hpp"

#include "../renderer/CCamera.hpp"

#include "CSound.hpp"

class CSoundManager final
{
friend class CEngine;

public:
	void	SetListener( const std::shared_ptr< const CCamera > &camera );

	// TODO - this is just for testing sound
	static void	Play( const std::shared_ptr< const CSound > &sound );

private:
	CSoundManager( const CSettings &settings );
	~CSoundManager( void );

	bool	Init( void );

	void	Update( void );

private:
	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	const unsigned int	m_buffer_size;
};

#endif // CSOUNDMANAGER_HPP
