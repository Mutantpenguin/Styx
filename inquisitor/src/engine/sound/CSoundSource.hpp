#ifndef CSOUNDSOURCE_HPP
#define CSOUNDSOURCE_HPP

#include <memory>

#include <glm/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#include "src/engine/sound/CSoundBuffer.hpp"

class CSoundSource final
{
private:
	CSoundSource( const CSoundSource& rhs );
	CSoundSource & operator=( const CSoundSource &rhs );

public:
	explicit CSoundSource( const std::shared_ptr< const CSoundBuffer > &soundBuffer );
	~CSoundSource();

	void SetSoundBuffer( const std::shared_ptr< const CSoundBuffer > &soundBuffer );

	const std::shared_ptr< const CSoundBuffer > Buffer( void ) const;

	void SetPosition( const glm::vec3 &position ) const;
	void SetLooping( const bool looping ) const;
	void SetRelativePositioning( const bool value ) const;

	void Play( void ) const;
	void Pause( void ) const;
	void Stop( void ) const;

private:
	std::shared_ptr< const CSoundBuffer > m_soundBuffer;

	ALuint m_sourceID;
};

#endif // CSOUNDSOURCE_HPP
