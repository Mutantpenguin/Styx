#include "CSoundManager.hpp"

#include <array>

#include "ALHelper.hpp"

#include "src/engine/logger/CLogger.hpp"

CSoundManager::CSoundManager( const CSettings &settings, const CFileSystem &p_filesystem, CResourceCacheManager &resourceCacheManager ) :
	m_buffer_size { settings.sound.buffer_size },
	m_resourceCacheManager { resourceCacheManager },
	m_soundBufferCache { std::make_shared< CSoundBufferCache >( p_filesystem ) }
{
	m_AL_device = alcOpenDevice( nullptr );
	if( nullptr == m_AL_device )
	{
		logERROR( "opening OpenAL device failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) );
		throw Exception();
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
		logERROR( "creating OpenAL context failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) );
		throw Exception();
	}

	if( !alcMakeContextCurrent( m_AL_context ) )
	{
		logERROR( "making OpenAL context current failed: {0}", ALHelper::GetOpenALErrorString( alGetError() ) );
		throw Exception();
	}

	logINFO( "\tVendor:  {0}", alGetString( AL_VENDOR ) );

	m_resourceCacheManager.Register< CSoundBuffer >( m_soundBufferCache );

	SetVolume( settings.sound.volume );

	logINFO( "sound manager was initialized" );
}

CSoundManager::~CSoundManager()
{
	logINFO( "sound manager is shutting down" );

	m_resourceCacheManager.DeRegister( m_soundBufferCache );

	alcDestroyContext( m_AL_context );

	alcCloseDevice( m_AL_device );
}

void CSoundManager::SetListener( const CTransform &transform )
{
	const glm::vec3 &position  = transform.Position();
	const glm::vec3 &direction = transform.Direction();
	const glm::vec3 &up        = transform.Up();

	alListener3f( AL_POSITION, position.x, position.y, position.z );

	const std::array< ALfloat, 6 > orientation = { { direction.x, direction.y, direction.z, up.x, up.y, up.z } };
	alListenerfv( AL_ORIENTATION, orientation.data() );
}

void CSoundManager::SetVolume( const f16 volume )
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
