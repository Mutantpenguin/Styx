#ifndef CFILESYSTEM_HPP
#define CFILESYSTEM_HPP

#include <exception>
#include <string>
#include <vector>

class CFileSystem final
{
public :
	using File = void;

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

	std::int64_t	Length( File *handle ) const;

	std::string	GetWriteDir( void ) const;
	bool			MakeDir( const std::string &dirname ) const;

	const char*	GetLastError( void ) const;

	static const char *GetDirSeparator( void );

	using FileBuffer = std::vector< std::uint8_t >;

	FileBuffer LoadFileToBuffer( const std::string &filename ) const;
	bool SaveBufferToFile( const FileBuffer &buffer, const std::string &filename ) const;

	std::string	LoadFileToString( const std::string &filename ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

/* TODO are these really needed anymore?
private:
	static std::int64_t	s_Read( void *buffer, std::size_t objSize, std::size_t objCount, File *handle );
	static std::int64_t	s_Write( void *buffer, std::size_t objSize, std::size_t objCount, File *handle );

	static std::int32_t	s_Seek( File *handle, std::int64_t pos, std::int32_t whence );
	static std::int64_t	s_Tell( File *handle );
*/

// TODO what to do with this?
	void InitialiseFreeImageIO( void );
};

#endif // CFILESYSTEM_HPP
