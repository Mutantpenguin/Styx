#include "CSoundManager.hpp"

#include "ALHelper.hpp"

#include "src/engine/logger/CLogger.hpp"

CSoundManager::CSoundManager( const CSettings &settings ) :
	m_buffer_size { settings.sound.buffer_size }
{
	m_AL_device = alcOpenDevice( nullptr );
	if( nullptr == m_AL_device )
	{
		logERROR( "opening OpenAL device failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) );
		throw std::exception();
	}

	ALint versionMajor;
	alcGetIntegerv( m_AL_device, ALC_MAJOR_VERSION, 1, &versionMajor );
	ALint versionMinor;
	alcGetIntegerv( m_AL_device, ALC_MAJOR_VERSION, 1, &versionMinor );

	logINFO( "OpenAL" );
	logINFO( "\t Version: {0}.{1}", versionMajor, versionMinor );
	logINFO( "\t Device:  {0}", alcGetString( m_AL_device, ALC_DEVICE_SPECIFIER ) );

	m_AL_context = alcCreateContext( m_AL_device, nullptr );
	if( nullptr == m_AL_context )
	{
		logERROR( "creating OpenAL context failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) );
		throw std::exception();
	}

	if( !alcMakeContextCurrent( m_AL_context ) )
	{
		logERROR( "making OpenAL context current failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) );
		throw std::exception();
	}

	ALenum error = alGetError();
	if( error != AL_NO_ERROR )
	{
		logERROR( "generating OpenAL buffers failed: {0}", ALHelper::GetOpenALErrorString( error ) );
		throw std::exception();
	}
}

CSoundManager::~CSoundManager( void )
{
	alcDestroyContext( m_AL_context );

	alcCloseDevice( m_AL_device );
}

// TODO - this is just temporary to test sound-output
void CSoundManager::Play( const std::shared_ptr< const CSound > &sound )
{
	ALuint bufferID;
	alGenBuffers( 1, &bufferID );

	const CSound::TSoundData &soundData = sound->SoundData();

	alBufferData( bufferID, ( sound->Format() == CSound::format::MONO ) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, soundData.data(), static_cast< ALsizei >( soundData.size() ), sound->Frequency() );

	ALuint sourceID;
	alGenSources( 1, &sourceID );

	alSource3f( sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f );
	alSourcei( sourceID, AL_LOOPING, AL_TRUE );

	alSourcei( sourceID, AL_BUFFER, bufferID );

	alSourcePlay( sourceID );
}

void CSoundManager::Update( void )
{
}

void CSoundManager::SetListener( const std::shared_ptr< const CCamera > &camera )
{
	const glm::vec3 &position = camera->Position();
	alListener3f( AL_POSITION, position.x, position.y, position.z );

	const glm::vec3 &direction	= camera->Direction();
	const glm::vec3 &up			= camera->Up();
	const std::array< ALfloat, 6 > orientation = { { direction.x, direction.y, direction.z, up.x, up.y, up.z } };
	alListenerfv( AL_ORIENTATION, orientation.data() );
}
