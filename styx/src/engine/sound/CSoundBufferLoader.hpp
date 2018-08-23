#ifndef CSOUNDLOADER_HPP
#define CSOUNDLOADER_HPP

#include <memory>

#include "src/engine/sound/CSoundBuffer.hpp"

#include "src/engine/system/CFileSystem.hpp"

class CSoundBufferLoader final
{
public:
	explicit CSoundBufferLoader( const CFileSystem &p_filesystem );
	~CSoundBufferLoader( void );

	void FromFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const;

private:
	using TSoundData = struct
	{
		std::vector< std::int16_t >	buffer;
		CSoundBuffer::format		format;
		std::uint32_t				frequency;
		float						duration;
	};

private:
	const CFileSystem &m_filesystem;

	bool FromOggFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const;
	bool FromWavFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const;

	void FromDummy( const std::shared_ptr< CSoundBuffer > &soundBuffer ) const;

	void FromTSoundData( const std::shared_ptr< CSoundBuffer > &soundBuffer, const TSoundData &soundData ) const;
};

#endif // CSOUNDLOADER_HPP
