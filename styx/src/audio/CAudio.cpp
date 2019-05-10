#include "CAudio.hpp"

#include <array>

#include "ALHelper.hpp"

#include "src/logger/CLogger.hpp"

#include "src/core/StyxException.hpp"

CAudio::CAudio( const CSettings &settings, const CFileSystem &p_filesystem, CResources &resources ) :
	m_buffer_size { settings.audio.buffer_size },
	m_resources { resources },
	m_audioBufferCache { std::make_shared<CAudioBufferCache>( p_filesystem ) }
{
	m_AL_device = alcOpenDevice( nullptr );
	if( nullptr == m_AL_device )
	{
		THROW_STYX_EXCEPTION( "opening OpenAL device failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) )
	}

	ALint versionMajor;
	alcGetIntegerv( m_AL_device, ALC_MAJOR_VERSION, 1, &versionMajor );
	ALint versionMinor;
	alcGetIntegerv( m_AL_device, ALC_MAJOR_VERSION, 1, &versionMinor );

	logINFO( "OpenAL" );
	logINFO( "\tVersion: {0}.{1}", versionMajor, versionMinor );
	logINFO( "\tDevice:  {0}", alcGetString( m_AL_device, ALC_DEVICE_SPECIFIER ) );


	m_AL_context = alcCreateContext( m_AL_device, nullptr );
	if( nullptr == m_AL_context )
	{
		THROW_STYX_EXCEPTION( "creating OpenAL context failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) )
	}

	if( !alcMakeContextCurrent( m_AL_context ) )
	{
		THROW_STYX_EXCEPTION( "making OpenAL context current failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) )
	}

	logINFO( "\tVendor:  {0}", alGetString( AL_VENDOR ) );

	m_resources.AddCache<CAudioBuffer>( m_audioBufferCache );

	SetVolume( settings.audio.volume );

	logINFO( "audio manager was initialized" );
}

CAudio::~CAudio()
{
	logINFO( "audio manager is shutting down" );

	m_resources.RemoveCache( m_audioBufferCache );

	alcDestroyContext( m_AL_context );

	alcCloseDevice( m_AL_device );
}

void CAudio::SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up )
{
	alListener3f( AL_POSITION, position.x, position.y, position.z );

	const std::array<ALfloat, 6> orientation = { { direction.x, direction.y, direction.z, up.x, up.y, up.z } };
	alListenerfv( AL_ORIENTATION, orientation.data() );
}

void CAudio::SetVolume( const f16 volume )
{
	f16 newVolume = volume;

	if( volume < 0.0f )
	{
		logWARNING( "volume was set too low: {0}", volume );
		newVolume = 0.0f;
	}
	else if( volume > 1.0f )
	{
		logWARNING( "volume was set too high: {0}", volume );
		newVolume = 1.0f;
	}

	alListenerf( AL_GAIN, newVolume );
}
