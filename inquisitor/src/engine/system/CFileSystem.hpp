#ifndef CFILESYSTEM_HPP
#define CFILESYSTEM_HPP

#include <exception>
#include <string>
#include <vector>

class CFileSystem final
{
public :
	using File = struct
	{
		void *opaque;  // that's all you get. don't touch!!
	};

	enum struct e_openmode : std::uint8_t
	{
		READ,
		WRITE,
		APPEND
	};

	CFileSystem( const char *argv0, const std::string &organisation, const std::string &gamename, const std::string &gamedir, const std::vector< std::string > &assets );
	~CFileSystem( void );

	bool			Exists( const std::string &filename ) const;
	bool			IsDirectory( const std::string &name ) const;
	bool			IsEOF( File *handle ) const;
	std::int64_t	GetLastModTime( const std::string &filename ) const;

	File*			Open( const std::string &filename, e_openmode openmode = e_openmode::READ ) const;
	void			Close( File *handle ) const;

	std::int64_t	Read( void *buffer, std::size_t objSize, std::size_t objCount, File *handle ) const;

	std::int64_t	Write( void *buffer, std::size_t objSize, std::size_t objCount, File *handle ) const;

	bool			Seek( File *handle, std::int64_t pos, std::uint8_t whence ) const;
	std::int64_t	Tell( File *handle ) const;

	std::int64_t	Length( File *handle ) const;

	std::string	GetWriteDir( void ) const;
	bool			MakeDir( const std::string &dirname ) const;

	const char*	GetLastError( void ) const;

	std::string	LoadTextFileToBuffer( const std::string &filename ) const;

	static const char *GetDirSeparator( void );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};
};

#endif // CFILESYSTEM_HPP
