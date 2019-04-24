#include "CAudioBufferLoader.hpp"

#include "src/logger/CLogger.hpp"

#include "external/stb/stb_vorbis.c"

#define DR_WAV_IMPLEMENTATION
#define DR_WAV_NO_STDIO
#include "external/dr_libs/dr_wav.h"

CAudioBufferLoader::CAudioBufferLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
	logINFO( "audio buffer loader was initialized" );
}

CAudioBufferLoader::~CAudioBufferLoader()
{
	logINFO( "audio buffer loader is shutting down" );
}

void CAudioBufferLoader::FromFile( const std::shared_ptr< CAudioBuffer > &audioBuffer, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", path.generic_string() );
		FromDummy( audioBuffer );
	}

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "audio file '{0}' does not exist", path.generic_string() );
		FromDummy( audioBuffer );
	}
	else
	{
		const std::string fileExtensionString = path.extension().generic_string();

		if( fileExtensionString == std::string( ".ogg" ) )
		{
			if( !FromOggFile( audioBuffer, path ) )
			{
				FromDummy( audioBuffer );
			}
		}
		else if( fileExtensionString == std::string( ".wav" ) )
		{
			if( !FromWavFile( audioBuffer, path ) )
			{
				FromDummy( audioBuffer );
			}
		}
		else
		{
			logWARNING( "file type '{0}' of audio file '{1}' is not supported", fileExtensionString, path.generic_string() );
		}
	}
}

bool CAudioBufferLoader::FromOggFile( const std::shared_ptr< CAudioBuffer > &audioBuffer, const fs::path &path ) const
{
	auto const fileBuffer = m_filesystem.LoadFileToBuffer( path );

	if( !fileBuffer.empty() )
	{
		i32 errorCode;

		stb_vorbis *stream = stb_vorbis_open_memory( reinterpret_cast<const unsigned char*>( fileBuffer.data() ), fileBuffer.size(), &errorCode, nullptr );

		if( nullptr == stream )
		{
			logWARNING( "not possible to open stream for ogg file '{0}': error code {1}", path.generic_string(), errorCode );
			return( false );
		}
		else
		{
			const stb_vorbis_info info = stb_vorbis_get_info( stream );

			const u32 lengthSamples = stb_vorbis_stream_length_in_samples( stream ) * info.channels * sizeof( i16 );

			TAudioData bufferDecoded;
			bufferDecoded.buffer.resize( lengthSamples );

			if( 0 == stb_vorbis_get_samples_short_interleaved( stream, info.channels, &bufferDecoded.buffer[ 0 ], lengthSamples ) )
			{
				logWARNING( "not possible to read samples from ogg file '{0}'", path.generic_string() );
				return( false );
			}

			bufferDecoded.duration = stb_vorbis_stream_length_in_seconds( stream );

			stb_vorbis_close( stream );

			bufferDecoded.format = ( 1 == info.channels ) ? CAudioBuffer::format::MONO : CAudioBuffer::format::STEREO;
			bufferDecoded.frequency = info.sample_rate;

			logDEBUG( "{0} / duration: {1:.0f}s / channels: {2} / sample rate: {3}", path.generic_string(), bufferDecoded.duration, info.channels, bufferDecoded.frequency );

			FromTAudioData( audioBuffer, bufferDecoded );

			return( true );
		}
	}
	else
	{
		logWARNING( "failed to load ogg file '{0}'", path.generic_string() );
		return( false );
	}
}

bool CAudioBufferLoader::FromWavFile( const std::shared_ptr< CAudioBuffer > &audioBuffer, const fs::path &path ) const
{
	auto const fileBuffer = m_filesystem.LoadFileToBuffer( path );

	if( !fileBuffer.empty() )
	{
		drwav wav;
		if( !drwav_init_memory( &wav, fileBuffer.data(), fileBuffer.size() ) )
		{
			logWARNING( "error opening wav file: {0}", path.generic_string() );
			return( false );
		}

		TAudioData bufferDecoded;
		bufferDecoded.buffer.resize( static_cast<size_t>( wav.totalPCMFrameCount * sizeof( i16 ) ) );

		bufferDecoded.duration = static_cast<f16>( wav.totalPCMFrameCount ) / static_cast<f16>( wav.sampleRate );
		bufferDecoded.format = ( 1 == wav.channels ) ? CAudioBuffer::format::MONO : CAudioBuffer::format::STEREO;
		bufferDecoded.frequency = wav.sampleRate;

		const auto numberOfPCMFramesActuallyDecoded = drwav_read_pcm_frames_s16( &wav, wav.totalPCMFrameCount, &bufferDecoded.buffer[ 0 ] );

		if( numberOfPCMFramesActuallyDecoded < wav.totalPCMFrameCount )
		{
			logWARNING( "expected {0} PCM frames but got {1} for wav file '{2}'", wav.totalPCMFrameCount, numberOfPCMFramesActuallyDecoded, path.generic_string() );
		}

		drwav_uninit( &wav );

		logDEBUG( "{0} / duration: {1:.0f}s / channels: {2} / sample rate: {3}", path.generic_string(), bufferDecoded.duration, wav.channels, bufferDecoded.frequency );

		FromTAudioData( audioBuffer, bufferDecoded );

		return( true );
	}
	else
	{
		logWARNING( "failed to load wav file '{0}'", path.generic_string() );
		return( false );
	}
}

void CAudioBufferLoader::FromTAudioData( const std::shared_ptr< CAudioBuffer > &audioBuffer, const TAudioData &audioData ) const
{
	audioBuffer->m_duration = audioData.duration;
	audioBuffer->m_format = audioData.format;

	alGenBuffers( 1, &audioBuffer->m_bufferID );

	alBufferData( audioBuffer->m_bufferID, ( audioData.format == CAudioBuffer::format::MONO ) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, audioData.buffer.data(), static_cast< ALsizei >( audioData.buffer.size() ), audioData.frequency );
}

void CAudioBufferLoader::FromDummy( const std::shared_ptr< CAudioBuffer > &audioBuffer ) const
{
	audioBuffer->Reset();
}
