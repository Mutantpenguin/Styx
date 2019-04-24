#pragma once

#include <memory>

#include "src/helper/Types.hpp"

#include "src/audio/CAudioBuffer.hpp"

#include "src/system/CFileSystem.hpp"

class CAudioBufferLoader final
{
public:
	explicit CAudioBufferLoader( const CFileSystem &p_filesystem );
	~CAudioBufferLoader();

	void FromFile( const std::shared_ptr< CAudioBuffer > &audioBuffer, const fs::path &path ) const;

private:
	using TAudioData = struct
	{
		std::vector< i16 >		buffer;
		CAudioBuffer::format	format;
		u32						frequency = 0;
		f16						duration = 0.0f;
	};

private:
	const CFileSystem &m_filesystem;

	bool FromOggFile( const std::shared_ptr< CAudioBuffer > &audioBuffer, const fs::path &path ) const;
	bool FromWavFile( const std::shared_ptr< CAudioBuffer > &audioBuffer, const fs::path &path ) const;

	void FromDummy( const std::shared_ptr< CAudioBuffer > &audioBuffer ) const;

	void FromTAudioData( const std::shared_ptr< CAudioBuffer > &audioBuffer, const TAudioData &audioData ) const;
};
