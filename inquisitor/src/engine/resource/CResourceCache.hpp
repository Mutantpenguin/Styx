#ifndef CRESOURCECACHE_HPP
#define CRESOURCECACHE_HPP

#include <string>

class CResourceCache
{
private:
	CResourceCache( const CResourceCache& rhs );
	CResourceCache& operator = ( const CResourceCache& rhs );

protected:
	CResourceCache( const std::string &name );
	virtual ~CResourceCache( void );

public:
	virtual void GarbageCollect( void ) = 0;
	virtual void Reload( void ) = 0;

	const std::string &Name( void );

protected:
	const std::string m_name;
};

#endif // CRESOURCECACHE_HPP
