#ifndef CFILESYSTEM_HPP
#define CFILESYSTEM_HPP

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
	~CFileSystem( void );

	bool	Exists( const std::string &filename ) const;
	bool	IsDirectory( const std::string &name ) const;
	i64		GetLastModTime( const std::string &filename ) const;

	std::string	GetWriteDir( void ) const;
	bool			MakeDir( const std::string &dirname ) const;

	const char*	GetLastError( void ) const;

	using FileBuffer = std::vector< u8 >;

	[[nodiscard]] FileBuffer LoadFileToBuffer( const std::string &filename ) const;
	bool SaveBufferToFile( const FileBuffer &buffer, const std::string &filename ) const;

	[[nodiscard]] std::string	LoadFileToString( const std::string &filename ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};


// TODO what to do with this?
	void InitialiseFreeImageIO( void );

private:
	CFileSystem( const CFileSystem &rhs ) = delete;
	CFileSystem& operator = ( const CFileSystem &rhs ) = delete;
};

#endif // CFILESYSTEM_HPP
