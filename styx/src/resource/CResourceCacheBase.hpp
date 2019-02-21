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
	virtual ~CResourceCacheBase();

public:
	virtual void CollectGarbage() = 0;
	virtual void Reload() = 0;

	const std::string &Name();

protected:
	const std::string m_name;
};
