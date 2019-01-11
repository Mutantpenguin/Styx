#pragma once

#include <exception>
#include <string>
#include <vector>

#include "src/engine/helper/Types.hpp"

class CFileSystem final
{
public :

	enum struct e_openmode : u8
	{
		READ,
		WRITE,
		APPEND
	};

	CFileSystem( const char *argv0, const std::string &organisation, const std::string &gamename, const std::string &gamedir, const std::vector< std::string > &assets );
	~CFileSystem();

	bool	Exists( const std::string &filename ) const;
	bool	IsDirectory( const std::string &name ) const;
	i64		GetLastModTime( const std::string &filename ) const;

	std::string	GetWriteDir() const;
	bool			MakeDir( const std::string &dirname ) const;

	const char*	GetLastError() const;

	using FileBuffer = std::vector< std::byte >;

	[[nodiscard]] FileBuffer LoadFileToBuffer( const std::string &filename ) const;
	bool SaveBufferToFile( const FileBuffer &buffer, const std::string &filename ) const;

	[[nodiscard]] std::string	LoadFileToString( const std::string &filename ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception() {}

		virtual ~Exception() throw() {}
	};


// TODO what to do with this?
	void InitialiseFreeImageIO();

private:
	CFileSystem( const CFileSystem &rhs ) = delete;
	CFileSystem& operator = ( const CFileSystem &rhs ) = delete;
};
