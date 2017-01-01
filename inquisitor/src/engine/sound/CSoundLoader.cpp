#include "CSoundLoader.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/ext/stb/stb_vorbis.c"

CSoundLoader::CSoundLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
}

std::shared_ptr< CSound > CSoundLoader::CreateSoundFromFile( const std::string &path ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "sound '{0}' does not exist", path );
		return( nullptr );
	}

	auto const fileBuffer = m_filesystem.LoadFileToBuffer( path );

	if( !fileBuffer.empty() )
	{
		std::int32_t errorCode;

		stb_vorbis *stream = stb_vorbis_open_memory( fileBuffer.data(), fileBuffer.size(), &errorCode, nullptr );

		if( nullptr == stream )
		{
			logWARNING( "not possible to open stream for ogg file '{0}': error code {1}", path, errorCode );
			return( nullptr );
		}
		else
		{
			const stb_vorbis_info info = stb_vorbis_get_info( stream );

			const std::uint32_t lengthSamples = stb_vorbis_stream_length_in_samples( stream ) * info.channels * sizeof( std::int16_t );

			CSound::TSoundData bufferDecoded( lengthSamples );

			if( 0 == stb_vorbis_get_samples_short_interleaved( stream, info.channels, &bufferDecoded[ 0 ], lengthSamples ) )
			{
				logWARNING( "not possible to read samples from ogg file '{0}'", path );
				return( nullptr );
			}

			const float duration = stb_vorbis_stream_length_in_seconds( stream );

			stb_vorbis_close( stream );

			const CSound::format format = ( 1 == info.channels ) ? CSound::format::MONO : CSound::format::STEREO;

			logDEBUG( "{0} / duration: {1:.0f}s / channels: {2} / sample rate: {3}", path, duration, info.channels, info.sample_rate );

			return( std::make_shared< CSound >( bufferDecoded, format, info.sample_rate, duration ) );
		}
	}
	else
	{
		logWARNING( "failed to open ogg file '{0}'", path );
		return( nullptr );
	}
}
