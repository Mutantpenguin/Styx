#include "SoundHandler.hpp"

#include "../logger/CLogger.hpp"

#include "../helper/CLibVorbisWrapper.hpp"

namespace SoundHandler
{
	std::shared_ptr< CSound > Load( const CFileSystem &p_filesystem, const std::string &path )
	{
		if( !p_filesystem.Exists( path ) )
		{
			LOG( logWARNING ) << "sound '" << path << "' does not exist";
			return( nullptr );
		}

		CFileSystem::File *f = p_filesystem.Open( path.c_str(), CFileSystem::e_openmode::READ );
		if( nullptr != f )
		{
			ov_callbacks &io = CLibVorbisWrapper::Get( p_filesystem );

			OggVorbis_File *ovf = new OggVorbis_File();

			ov_open_callbacks( static_cast< void* >( f ), ovf, nullptr, -1, io );

			const vorbis_info *vi = ov_info( ovf, -1 );

			LOG( logDEBUG ) << "version: " << vi->version << " / channels: " << vi->channels << " / rate: " << vi->rate;

			std::array< char, 32768 > tempBuffer;

			CSound::TSoundData buffer;

			int bitStream;

			unsigned int frequency = vi->rate;

			long bytes;

			const CSound::format format = ( 1 == vi->channels ) ? CSound::format::MONO : CSound::format::STEREO;

			do
			{
				bytes = ov_read( ovf, tempBuffer.data(), tempBuffer.size(), 0, 2, 1, &bitStream );

				buffer.insert( buffer.end(), tempBuffer.data(), tempBuffer.data() + bytes );
			} while( bytes > 0 );

			ov_clear( ovf );

			return( std::make_shared< CSound >( buffer, format, frequency ) );
		}
		else
		{
			LOG( logWARNING ) << "failed to open '" << path << "'";
		}

		return( nullptr );
	}
}
