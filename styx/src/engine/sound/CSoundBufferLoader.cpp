#include "CSoundBufferLoader.hpp"

#include <exception>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/helper/Path.hpp"

#include "src/ext/stb/stb_vorbis.c"

#define DR_WAV_IMPLEMENTATION
#define DR_WAV_NO_STDIO
#include "src/ext/dr_libs/dr_wav.h"

CSoundBufferLoader::CSoundBufferLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
	logINFO( "sound buffer loader was initialized" );
}

CSoundBufferLoader::~CSoundBufferLoader()
{
	logINFO( "sound buffer loader is shutting down" );
}

void CSoundBufferLoader::FromFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "sound file '{0}' does not exist", path );
		FromDummy( soundBuffer );
	}
	else
	{
		const std::string fileExtension = Path::Extension( path );

		if( fileExtension == std::string( "ogg" ) )
		{
			if( !FromOggFile( soundBuffer, path ) )
			{
				FromDummy( soundBuffer );
			}
		}
		else if( fileExtension == std::string( "wav" ) )
		{
			if( !FromWavFile( soundBuffer, path ) )
			{
				FromDummy( soundBuffer );
			}
		}
		else
		{
			logWARNING( "file type '{0}' of sound file '{1}' is not supported", fileExtension, path );
		}
	}
}

bool CSoundBufferLoader::FromOggFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const
{
	auto const fileBuffer = m_filesystem.LoadFileToBuffer( path );

	if( !fileBuffer.empty() )
	{
		i32 errorCode;

		stb_vorbis *stream = stb_vorbis_open_memory( fileBuffer.data(), fileBuffer.size(), &errorCode, nullptr );

		if( nullptr == stream )
		{
			logWARNING( "not possible to open stream for ogg file '{0}': error code {1}", path, errorCode );
			return( false );
		}
		else
		{
			const stb_vorbis_info info = stb_vorbis_get_info( stream );

			const u32 lengthSamples = stb_vorbis_stream_length_in_samples( stream ) * info.channels * sizeof( i16 );

			TSoundData bufferDecoded;
			bufferDecoded.buffer.resize( lengthSamples );

			if( 0 == stb_vorbis_get_samples_short_interleaved( stream, info.channels, &bufferDecoded.buffer[ 0 ], lengthSamples ) )
			{
				logWARNING( "not possible to read samples from ogg file '{0}'", path );
				return( false );
			}

			bufferDecoded.duration = stb_vorbis_stream_length_in_seconds( stream );

			stb_vorbis_close( stream );

			bufferDecoded.format = ( 1 == info.channels ) ? CSoundBuffer::format::MONO : CSoundBuffer::format::STEREO;
			bufferDecoded.frequency = info.sample_rate;

			logDEBUG( "{0} / duration: {1:.0f}s / channels: {2} / sample rate: {3}", path, bufferDecoded.duration, info.channels, bufferDecoded.frequency );

			FromTSoundData( soundBuffer, bufferDecoded );

			return( true );
		}
	}
	else
	{
		logWARNING( "failed to load ogg file '{0}'", path );
		return( false );
	}
}

bool CSoundBufferLoader::FromWavFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const
{
	auto const fileBuffer = m_filesystem.LoadFileToBuffer( path );

	if( !fileBuffer.empty() )
	{
		drwav wav;
		if( !drwav_init_memory( &wav, fileBuffer.data(), fileBuffer.size() ) )
		{
			logWARNING( "error opening wav file: {0}", path );
			return( false );
		}

		TSoundData bufferDecoded;
		bufferDecoded.buffer.resize( static_cast<size_t>( wav.totalSampleCount * sizeof( i16 ) ) );

		bufferDecoded.duration = static_cast<f16>( wav.totalSampleCount ) / static_cast<f16>( wav.sampleRate );
		bufferDecoded.format = ( 1 == wav.channels ) ? CSoundBuffer::format::MONO : CSoundBuffer::format::STEREO;
		bufferDecoded.frequency = wav.sampleRate;

		const auto numberOfSamplesActuallyDecoded = drwav_read_s16( &wav, wav.totalSampleCount, &bufferDecoded.buffer[ 0 ] );

		if( numberOfSamplesActuallyDecoded < wav.totalSampleCount )
		{
			logWARNING( "expected {0} samples but got {1} for wav file '{2}'", wav.totalSampleCount, numberOfSamplesActuallyDecoded, path );
		}

		drwav_uninit( &wav );

		logDEBUG( "{0} / duration: {1:.0f}s / channels: {2} / sample rate: {3}", path, bufferDecoded.duration, wav.channels, bufferDecoded.frequency );

		FromTSoundData( soundBuffer, bufferDecoded );

		return( true );
	}
	else
	{
		logWARNING( "failed to load wav file '{0}'", path );
		return( false );
	}
}

void CSoundBufferLoader::FromTSoundData( const std::shared_ptr< CSoundBuffer > &soundBuffer, const TSoundData &soundData ) const
{
	soundBuffer->m_duration = soundData.duration;
	soundBuffer->m_format = soundData.format;

	alGenBuffers( 1, &soundBuffer->m_bufferID );

	alBufferData( soundBuffer->m_bufferID, ( soundData.format == CSoundBuffer::format::MONO ) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, soundData.buffer.data(), static_cast< ALsizei >( soundData.buffer.size() ), soundData.frequency );
}

void CSoundBufferLoader::FromDummy( const std::shared_ptr< CSoundBuffer > &soundBuffer ) const
{
	soundBuffer->Reset();
}
