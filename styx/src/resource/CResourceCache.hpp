#pragma once

#include <memory>
#include <map>
#include <string>

#include "src/core/Types.hpp"

#include "src/resource/CResourceCacheBase.hpp"

#include "src/logger/CLogger.hpp"

#include "src/system/CFileSystem.hpp"


template<typename T>
class CResourceCache : public CResourceCacheBase
{
	// TODO static_assert T::Reset

private:
	CResourceCache( const CResourceCache& rhs ) = delete;
	CResourceCache& operator = ( const CResourceCache& rhs ) = delete;

protected:
	CResourceCache( const std::string &name, const CFileSystem &p_filesystem ) :
		CResourceCacheBase( name ),
		m_filesystem { p_filesystem }
	{}

	virtual ~CResourceCache()
	{
		#ifdef STYX_DEBUG
		if( !m_resources.empty() )
		{
			logERROR( "there are still '{0}' resources in '{1}' cache", m_resources.size(), m_name );

			for( const auto & [ path, resourceInfo ] : m_resources )
			{
				logWARNING( "\t{0}: {1}", path, resourceInfo.resource.use_count() - 1 );
			}
		}
		#endif
	}

public:
	[[nodiscard]] const std::shared_ptr<const T> Get( const std::string &path )
	{
		const auto it = m_resources.find( path );
		
		if( std::end( m_resources ) != it )
		{
			return( it->second.resource );
		}

		auto newResource = std::make_shared<T>();

		Load( newResource, path );

		auto &resourceInfo = m_resources[ path ];

		resourceInfo.resource = newResource;
		resourceInfo.mtime    = GetMtime( path );

		return( newResource );
	}

	void CollectGarbage() override final
	{
		for( auto it = std::cbegin( m_resources ); it != std::cend( m_resources ); )
		{
			if( it->second.resource.unique() )
			{
				m_resources.erase( it++ );
			}
			else
			{
				++it;
			}
		}
	}

	void Reload() override final
	{
		logINFO( "reloading cache: {0}", m_name );

		for( auto & [ path, resourceInfo ] : m_resources )
		{
			const auto currentMtime = GetMtime( path );
			if( currentMtime > resourceInfo.mtime )
			{
				logINFO( "\t{0}", path );

				resourceInfo.resource->Reset();

				Load( resourceInfo.resource, path );

				resourceInfo.mtime = currentMtime;
			}
		}
	}


protected:
	const CFileSystem &m_filesystem;

private:
	virtual void Load( const std::shared_ptr<T> &resource, const std::string &path ) const = 0;
	
	virtual i64 GetMtime( const std::string &path ) final
	{
		return( m_filesystem.GetLastModTime( path ) );
	}
	
	struct sResourceInfo
	{
		std::shared_ptr<T>	resource;
		i64					mtime = 0;
	};

	std::map<std::string, sResourceInfo> m_resources;
};
