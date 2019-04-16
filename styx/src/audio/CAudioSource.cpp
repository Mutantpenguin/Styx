#include "CAudioSource.hpp"

CAudioSource::CAudioSource( const std::shared_ptr< const CAudioBuffer > &audioBuffer )
{
	alGenSources( 1, &m_sourceID );

	SetAudioBuffer( audioBuffer );

	SetPosition( { 0.0f, 0.0f, 0.0f } );

	SetLooping( false );
}

CAudioSource::~CAudioSource()
{
	alDeleteSources( 1, &m_sourceID );
}

void CAudioSource::SetAudioBuffer( const std::shared_ptr< const CAudioBuffer > &audioBuffer )
{
	m_audioBuffer = audioBuffer;

	alSourcei( m_sourceID, AL_BUFFER, audioBuffer->m_bufferID );
}

const std::shared_ptr< const CAudioBuffer > CAudioSource::Buffer() const
{
	return( m_audioBuffer );
}

void CAudioSource::SetPosition( const glm::vec3 &position ) const
{
	alSource3f( m_sourceID, AL_POSITION, position.x, position.y, position.z );
}

void CAudioSource::SetLooping( const bool looping ) const
{
	alSourcei( m_sourceID, AL_LOOPING, looping ? AL_TRUE : AL_FALSE );
}

void CAudioSource::SetRelativePositioning( const bool value ) const
{
	alSourcei( m_sourceID, AL_SOURCE_RELATIVE, value ? AL_TRUE : AL_FALSE );
}

void CAudioSource::Play() const
{
	alSourcePlay( m_sourceID );
}

void CAudioSource::Pause() const
{
	alSourcePause( m_sourceID );
}

void CAudioSource::Stop() const
{
	alSourceStop( m_sourceID );
}
