#ifndef CFILESYSTEM_HPP
#define CFILESYSTEM_HPP

#include <string>
#include <vector>

class CFileSystem final
{
public :
	typedef struct
	{
		void *opaque;  // that's all you get. don't touch!!
	} File;

	enum struct e_openmode : unsigned char
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
	unsigned long long GetLastModTime( const std::string &filename ) const;

	File*			Open( const std::string &filename, e_openmode openmode = e_openmode::READ ) const;
	void			Close( File *handle ) const;

	long long		Read( void *buffer, unsigned int objSize, unsigned int objCount, File *handle ) const;

	long long		Write( void *buffer, unsigned int objSize, unsigned int objCount, File *handle ) const;

	bool			Seek( File *handle, unsigned long long pos, int whence ) const;
	long long		Tell( File *handle ) const;

	long long		Length( File *handle ) const;

	std::string	GetWriteDir( void ) const;
	bool			MakeDir( const std::string &dirname ) const;

	const char*	GetLastError( void ) const;

	std::string	LoadTextFileToBuffer( const std::string &filename ) const;

	static const char *GetDirSeparator( void );
};

#endif // CFILESYSTEM_HPP
