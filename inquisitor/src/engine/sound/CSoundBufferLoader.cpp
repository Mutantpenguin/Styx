#include "CSoundBufferLoader.hpp"

#include <exception>

#include "src/engine/logger/CLogger.hpp"

#include "src/ext/stb/stb_vorbis.c"

CSoundBufferLoader::CSoundBufferLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
}

void CSoundBufferLoader::FromFile( const std::string &path, std::shared_ptr< CSoundBuffer > &soundBuffer ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "sound file '{0}' does not exist", path );
		FromDummy( soundBuffer );
	}
	else
	{
		const std::string fileExtension = path.substr( path.find_last_of( "." ) + 1 );

		if( fileExtension == std::string( "ogg" ) )
		{
			if( !FromOggFile( path, soundBuffer ) )
			{
				FromDummy( soundBuffer );
			}
		}
		/* TODO implement loading of WAV
		else if( fileExtension == std::string( "wav" ) )
		{
		}*/
		else
		{
			logWARNING( "file type '{0}' of sound file '{1}' is not supported", fileExtension, path );
		}
	}
}

bool CSoundBufferLoader::FromOggFile( const std::string &path, std::shared_ptr< CSoundBuffer > &soundBuffer ) const
{
	auto const fileBuffer = m_filesystem.LoadFileToBuffer( path );

	if( !fileBuffer.empty() )
	{
		std::int32_t errorCode;

		stb_vorbis *stream = stb_vorbis_open_memory( fileBuffer.data(), fileBuffer.size(), &errorCode, nullptr );

		if( nullptr == stream )
		{
			logWARNING( "not possible to open stream for ogg file '{0}': error code {1}", path, errorCode );
			return( false );
		}
		else
		{
			const stb_vorbis_info info = stb_vorbis_get_info( stream );

			const std::uint32_t lengthSamples = stb_vorbis_stream_length_in_samples( stream ) * info.channels * sizeof( std::int16_t );

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

			FromTSoundData( bufferDecoded, soundBuffer );

			return( true );
		}
	}
	else
	{
		logWARNING( "failed to load ogg file '{0}'", path );
		return( false );
	}
}

void CSoundBufferLoader::FromTSoundData( const TSoundData &soundData, std::shared_ptr< CSoundBuffer > &soundBuffer ) const
{
	soundBuffer->m_duration = soundData.duration;
	soundBuffer->m_format = soundData.format;

	alGenBuffers( 1, &soundBuffer->m_bufferID );

	alBufferData( soundBuffer->m_bufferID, ( soundData.format == CSoundBuffer::format::MONO ) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, soundData.buffer.data(), static_cast< ALsizei >( soundData.buffer.size() ), soundData.frequency );
}

void CSoundBufferLoader::FromDummy( std::shared_ptr< CSoundBuffer > &soundBuffer ) const
{
	soundBuffer->Reset();
}
