#pragma once

#include <memory>
#include <map>
#include <string>

#include "src/helper/Types.hpp"

#include "src/resource/CResourceCacheBase.hpp"

#include "src/logger/CLogger.hpp"

#include "src/system/CFileSystem.hpp"


template < typename T >
class CResourceCache : public CResourceCacheBase
{
	// TODO static_assert T::Reset
	// TODO static_assert T::ResourceIdType
	// TODO static_assert T::ToString

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

			for( const auto & [ id, resourceInfo ] : m_resources )
			{
				// BUG list every resource / doesn't work right now because we can't call virtual methods of derived classes
				//logDEBUG( "\t{0}: {1}", GetIdAsString( id ), resourceInfo.resource.use_count() );
			}
		}
		#endif
	}

public:
	[[nodiscard]] const std::shared_ptr< const T > GetResource( const typename T::ResourceIdType &id )
	{
		const auto it = m_resources.find( id );
		if( std::end( m_resources ) != it )
		{
			return( it->second.resource );
		}

		auto newResource = std::make_shared< T >();

		Load( newResource, id );

		auto &resourceInfo = m_resources[ id ];

		resourceInfo.resource = newResource;
		resourceInfo.mtime    = GetMtime( id );

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

		for( auto & [ id, resourceInfo ] : m_resources )
		{
			const auto currentMtime = GetMtime( id );
			if( currentMtime > resourceInfo.mtime )
			{
				logINFO( "\t{0}", GetIdAsString( id ) );

				resourceInfo.resource->Reset();

				Load( resourceInfo.resource, id );

				resourceInfo.mtime = currentMtime;
			}
		}
	}


protected:
	const CFileSystem &m_filesystem;

private:
	virtual void Load( const std::shared_ptr< T > &resource, const typename T::ResourceIdType &id ) const = 0;

	virtual i64 GetMtime( const typename T::ResourceIdType &id ) const = 0;

	virtual std::string GetIdAsString( const typename T::ResourceIdType &id ) = 0;

	struct sResourceInfo
	{
		std::shared_ptr< T >	resource;
		i64						mtime;
	};

	std::map< typename T::ResourceIdType, sResourceInfo > m_resources;
};
