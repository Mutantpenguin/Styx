#pragma once

#include <string>
#include <memory>

class CResourceCacheBase
{
private:
	CResourceCacheBase( const CResourceCacheBase& rhs );
	CResourceCacheBase& operator = ( const CResourceCacheBase& rhs );

protected:
	explicit CResourceCacheBase( const std::string &name );
	virtual ~CResourceCacheBase( void );

public:
	virtual void CollectGarbage( void ) = 0;
	virtual void Reload( void ) = 0;

	const std::string &Name( void );

protected:
	const std::string m_name;
};
