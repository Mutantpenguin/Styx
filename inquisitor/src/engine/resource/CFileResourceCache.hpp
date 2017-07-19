#ifndef CFILERESOURCECACHE_HPP
#define CFILERESOURCECACHE_HPP

#include <memory>
#include <unordered_map>

#include "src/engine/resource/CAbstractResourceCache.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/system/CFileSystem.hpp"


template <typename TResource>
class CFileResourceCache : public CAbstractResourceCache
{
private:
	CFileResourceCache( const CFileResourceCache& rhs );
	CFileResourceCache& operator = ( const CFileResourceCache& rhs );

protected:
	CFileResourceCache( const std::string name, const CFileSystem &p_filesystem ) :
		CAbstractResourceCache( name ),
		m_filesystem { p_filesystem }
	{}

	virtual ~CFileResourceCache( void )
	{
		if( !m_resourceFiles.empty() )
		{
			logWARNING( "there are still '{0}' resources in '{1}' cache", m_resourceFiles.size(), m_name );
			#ifdef INQ_DEBUG
			for( const auto & [ filename, resourceFile ] : m_resourceFiles )
			{
				logDEBUG( "\t{0}: {1}", filename, resourceFile.resource.use_count() );
			}
			#endif
		}
	}

public:
	[[nodiscard]] const std::shared_ptr< const TResource > Get( const std::string &path )
	{
		const auto it = m_resourceFiles.find( path );
		if( std::end( m_resourceFiles ) != it )
		{
			return( it->second.resource );
		}

		auto newResource = std::make_shared< TResource >();

		FromFile( path, newResource );

		auto &resourceFile = m_resourceFiles[ path ];

		resourceFile.resource = newResource;
		resourceFile.mtime    = m_filesystem.GetLastModTime( path );

		return( newResource );
	}

	void GarbageCollect( void ) override final
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
		logINFO( "reloading '{0}' cache:", m_name );

		for( auto & [ filename, resourceFile ] : m_resourceFiles )
		{
			const auto mtime = m_filesystem.GetLastModTime( filename );
			if( mtime > resourceFile.mtime )
			{
				logINFO( "\t{0}", filename );

				resourceFile.resource->Reset();

				FromFile( filename, resourceFile.resource );

				resourceFile.mtime = mtime;
			}
		}
	}

private:
	virtual void FromFile( const std::string &path, std::shared_ptr< TResource > &resource ) = 0;

	struct sResourceFile
	{
		std::shared_ptr< TResource >	resource;
		std::int64_t					mtime;
	};

	const CFileSystem &m_filesystem;

	std::unordered_map< std::string, sResourceFile > m_resourceFiles;
};

#endif // CFILERESOURCECACHE_HPP
