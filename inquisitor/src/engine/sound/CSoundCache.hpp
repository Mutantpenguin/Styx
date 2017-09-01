#ifndef CSOUNDCACHE_HPP
#define CSOUNDCACHE_HPP

#include "CResourceCache.hpp" // Base class: CResourceCache

class CSoundCache : public CResourceCache
{
private:
	CSoundCache(const CSoundCache& rhs);
	CSoundCache& operator=(const CSoundCache& rhs);

public:
	CSoundCache();
	~CSoundCache();

public:
	virtual
void LoadFromFile(const std::shared_ptr<T>& resource, const std::string& path);
};

#endif // CSOUNDCACHE_HPP
