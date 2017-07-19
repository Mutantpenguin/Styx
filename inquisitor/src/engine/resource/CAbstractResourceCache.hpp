#ifndef CABSTRACTRESOURCECACHE_HPP
#define CABSTRACTRESOURCECACHE_HPP

#include <string>

class CAbstractResourceCache
{
private:
	CAbstractResourceCache( const CAbstractResourceCache& rhs );
	CAbstractResourceCache& operator = ( const CAbstractResourceCache& rhs );

protected:
	CAbstractResourceCache( const std::string &name );
	virtual ~CAbstractResourceCache( void );

public:
	virtual void GarbageCollect( void ) = 0;
	virtual void Reload( void ) = 0;

	const std::string &Name( void );

protected:
	const std::string m_name;
};

#endif // CABSTRACTRESOURCECACHE_HPP
