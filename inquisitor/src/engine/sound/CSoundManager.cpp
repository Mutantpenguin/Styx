#include "CSoundManager.hpp"

#include "ALHelper.hpp"

#include "src/engine/logger/CLogger.hpp"

CSoundManager::CSoundManager( const CSettings &settings, const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem },
	m_soundBufferloader { p_filesystem },
	m_buffer_size { settings.sound.buffer_size }
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
}

CSoundManager::~CSoundManager( void )
{
	alcDestroyContext( m_AL_context );

	alcCloseDevice( m_AL_device );
}

std::shared_ptr< CSoundBuffer > CSoundManager::LoadSoundBuffer( const std::string &path )
{
	const auto it = m_soundBufferFiles.find( path );
	if( std::end( m_soundBufferFiles ) != it )
	{
		return( it->second.soundBuffer );
	}

	auto newSoundBuffer = std::make_shared< CSoundBuffer >();

	m_soundBufferloader.FromFile( path, newSoundBuffer );

	auto &soundBufferFile = m_soundBufferFiles[ path ];

	soundBufferFile.soundBuffer = newSoundBuffer;
	soundBufferFile.mtime 		= m_filesystem.GetLastModTime( path );

	return( newSoundBuffer );
}

void CSoundManager::Update( void )
{
	for( auto it = std::cbegin( m_soundBufferFiles ); it != std::cend( m_soundBufferFiles ); )
	{
		if( it->second.soundBuffer.unique() )
		{
			m_soundBufferFiles.erase( it++ );
		}
		else
		{
			++it;
		}
	}
}

void CSoundManager::SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up )
{
	alListener3f( AL_POSITION, position.x, position.y, position.z );

	const std::array< ALfloat, 6 > orientation = { { direction.x, direction.y, direction.z, up.x, up.y, up.z } };
	alListenerfv( AL_ORIENTATION, orientation.data() );
}

// TODO where to call?
void CSoundManager::ReloadSoundBuffers( void )
{
	logINFO( "reloading sound buffers:" );

	for( auto & [ filename, soundBufferFile ] : m_soundBufferFiles )
	{
		const auto mtime = m_filesystem.GetLastModTime( filename );
		if( mtime > soundBufferFile.mtime )
		{
			logINFO( "    {0}", filename );

			soundBufferFile.soundBuffer->Reset();

			m_soundBufferloader.FromFile( filename, soundBufferFile.soundBuffer );

			soundBufferFile.mtime = mtime;
		}
	}
}
