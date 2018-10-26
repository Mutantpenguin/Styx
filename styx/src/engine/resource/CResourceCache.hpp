#ifndef CESOURCECACHE_HPP
#define CESOURCECACHE_HPP

#include <memory>
#include <unordered_map>

#include "src/engine/helper/Types.hpp"

#include "src/engine/resource/CResourceCacheBase.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/system/CFileSystem.hpp"


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

	virtual ~CResourceCache( void )
	{
		#ifdef STYX_DEBUG
		if( !m_resourceFiles.empty() )
		{
			logWARNING( "there are still '{0}' resources in '{1}' cache", m_resourceFiles.size(), m_name );

			for( const auto & [ filename, resourceFile ] : m_resourceFiles )
			{
				logDEBUG( "\t{0}: {1}", filename, resourceFile.resource.use_count() );
			}
		}
		#endif
	}

public:
	[[nodiscard]] const std::shared_ptr< const T > GetResource( const std::string &path )
	{
		const auto it = m_resourceFiles.find( path );
		if( std::end( m_resourceFiles ) != it )
		{
			return( it->second.resource );
		}

		auto newResource = std::make_shared< T >();

		LoadFromFile( newResource, path );

		auto &resourceFile = m_resourceFiles[ path ];

		resourceFile.resource = newResource;
		resourceFile.mtime    = m_filesystem.GetLastModTime( path );

		return( newResource );
	}

	void CollectGarbage( void ) override final
	{
		for( auto it = std::cbegin( m_resourceFiles ); it != std::cend( m_resourceFiles ); )
		{
			if( it->second.resource.unique() )
			{
				m_resourceFiles.erase( it++ );
			}
			else
			{
				++it;
			}
		}
	}

	void Reload( void ) override final
	{
		logINFO( "reloading cache: {0}", m_name );

		for( auto & [ filename, resourceFile ] : m_resourceFiles )
		{
			const auto currentMtime = m_filesystem.GetLastModTime( filename );
			if( currentMtime > resourceFile.mtime )
			{
				logINFO( "\t{0}", filename );

				resourceFile.resource->Reset();

				LoadFromFile( resourceFile.resource, filename );

				resourceFile.mtime = currentMtime;
			}
		}
	}

private:
	virtual void LoadFromFile( const std::shared_ptr< T > &resource, const std::string &path ) = 0;

	struct sResourceFile
	{
		std::shared_ptr< T >	resource;
		i64						mtime;
	};

	const CFileSystem &m_filesystem;

	std::unordered_map< std::string, sResourceFile > m_resourceFiles;
};

#endif // CESOURCECACHE_HPP
