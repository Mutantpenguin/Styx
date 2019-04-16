#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#include "src/audio/CAudioBuffer.hpp"

class CAudioSource final
{
private:
	CAudioSource( const CAudioSource& rhs );
	CAudioSource & operator=( const CAudioSource &rhs );

public:
	explicit CAudioSource( const std::shared_ptr< const CAudioBuffer > &audioBuffer );
	~CAudioSource();

	void SetAudioBuffer( const std::shared_ptr< const CAudioBuffer > &audioBuffer );

	const std::shared_ptr< const CAudioBuffer > Buffer() const;

	void SetPosition( const glm::vec3 &position ) const;
	void SetLooping( const bool looping ) const;
	void SetRelativePositioning( const bool value ) const;

	void Play() const;
	void Pause() const;
	void Stop() const;

private:
	std::shared_ptr< const CAudioBuffer > m_audioBuffer;

	ALuint m_sourceID;
};
