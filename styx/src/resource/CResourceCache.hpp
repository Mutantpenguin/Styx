#pragma once

#include <memory>
#include <unordered_map>

#include "src/helper/Types.hpp"

#include "src/resource/CResourceCacheBase.hpp"

#include "src/logger/CLogger.hpp"

#include "src/system/CFileSystem.hpp"


template < typename T >
class CResourceCache : public CResourceCacheBase
{
private:
	CResourceCache( const CResourceCache& rhs );
	CResourceCache& operator = ( const CResourceCache& rhs );

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
			logWARNING( "there are still '{0}' resources in '{1}' cache", m_resources.size(), m_name );

			for( const auto & [ filename, resourceFile ] : m_resources )
			{
				logDEBUG( "\t{0}: {1}", filename, resourceFile.resource.use_count() );
			}
		}
		#endif
	}

public:
	[[nodiscard]] const std::shared_ptr< const T > GetResource( const std::string &path )
	{
		const auto it = m_resources.find( path );
		if( std::end( m_resources ) != it )
		{
			return( it->second.resource );
		}

		auto newResource = std::make_shared< T >();

		Load( newResource, path );

		auto &resourceFile = m_resources[ path ];

		resourceFile.resource = newResource;
		resourceFile.mtime    = m_filesystem.GetLastModTime( path );

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

		for( auto & [ filename, resourceFile ] : m_resources )
		{
			const auto currentMtime = m_filesystem.GetLastModTime( filename );
			if( currentMtime > resourceFile.mtime )
			{
				logINFO( "\t{0}", filename );

				resourceFile.resource->Reset();

				Load( resourceFile.resource, filename );

				resourceFile.mtime = currentMtime;
			}
		}
	}

private:
	virtual void Load( const std::shared_ptr< T > &resource, const std::string &path ) = 0;

	struct sResource
	{
		std::shared_ptr< T >	resource;
		i64						mtime;
	};

	const CFileSystem &m_filesystem;

	std::unordered_map< std::string, sResource > m_resources;
};
