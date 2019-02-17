#include "CSoundSource.hpp"

CSoundSource::CSoundSource( const std::shared_ptr< const CSoundBuffer > &soundBuffer )
{
	alGenSources( 1, &m_sourceID );

	SetSoundBuffer( soundBuffer );

	SetPosition( { 0.0f, 0.0f, 0.0f } );

	SetLooping( false );
}

CSoundSource::~CSoundSource()
{
	alDeleteSources( 1, &m_sourceID );
}

void CSoundSource::SetSoundBuffer( const std::shared_ptr< const CSoundBuffer > &soundBuffer )
{
	m_soundBuffer = soundBuffer;

	alSourcei( m_sourceID, AL_BUFFER, soundBuffer->m_bufferID );
}

const std::shared_ptr< const CSoundBuffer > CSoundSource::Buffer() const
{
	return( m_soundBuffer );
}

void CSoundSource::SetPosition( const glm::vec3 &position ) const
{
	alSource3f( m_sourceID, AL_POSITION, position.x, position.y, position.z );
}

void CSoundSource::SetLooping( const bool looping ) const
{
	alSourcei( m_sourceID, AL_LOOPING, looping ? AL_TRUE : AL_FALSE );
}

void CSoundSource::SetRelativePositioning( const bool value ) const
{
	alSourcei( m_sourceID, AL_SOURCE_RELATIVE, value ? AL_TRUE : AL_FALSE );
}

void CSoundSource::Play() const
{
	alSourcePlay( m_sourceID );
}

void CSoundSource::Pause() const
{
	alSourcePause( m_sourceID );
}

void CSoundSource::Stop() const
{
	alSourceStop( m_sourceID );
}
