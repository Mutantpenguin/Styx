#pragma once

#include <memory>

#include "src/helper/Types.hpp"

#include "src/sound/CSoundBuffer.hpp"

#include "src/system/CFileSystem.hpp"

class CSoundBufferLoader final
{
public:
	explicit CSoundBufferLoader( const CFileSystem &p_filesystem );
	~CSoundBufferLoader();

	void FromFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const;

private:
	using TSoundData = struct
	{
		std::vector< i16 >		buffer;
		CSoundBuffer::format	format;
		u32						frequency;
		f16						duration;
	};

private:
	const CFileSystem &m_filesystem;

	bool FromOggFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const;
	bool FromWavFile( const std::shared_ptr< CSoundBuffer > &soundBuffer, const std::string &path ) const;

	void FromDummy( const std::shared_ptr< CSoundBuffer > &soundBuffer ) const;

	void FromTSoundData( const std::shared_ptr< CSoundBuffer > &soundBuffer, const TSoundData &soundData ) const;
};
