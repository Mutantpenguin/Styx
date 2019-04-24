#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

#include "src/helper/Types.hpp"

class CFileSystem final
{
public :

	enum struct e_openmode : u8
	{
		READ,
		WRITE,
		APPEND
	};

	CFileSystem( const char *argv0, const std::string &organisation, const std::string &gamename, const fs::path &gameDirectory, const std::vector< std::string > &assets );
	~CFileSystem();

	bool	Exists( const fs::path &path ) const;
	bool	IsDirectory( const fs::path &path ) const;
	i64		GetLastModTime( const fs::path &path ) const;

	bool	MakeDir( const fs::path &path ) const;

	const char*	GetLastError() const;

	using FileBuffer = std::vector< std::byte >;

	[[nodiscard]] FileBuffer	LoadFileToBuffer( const fs::path &path ) const;
	[[nodiscard]] bool			SaveBufferToFile( const FileBuffer &buffer, const fs::path &path ) const;

	[[nodiscard]] std::string	LoadFileToString( const fs::path &path ) const;

private:
	CFileSystem( const CFileSystem &rhs ) = delete;
	CFileSystem& operator = ( const CFileSystem &rhs ) = delete;
};
