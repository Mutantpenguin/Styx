#pragma once

#include <string>
#include <memory>
#include <array>

#include "src/scene/CTransform.hpp"

#include "src/scene/components/EComponentIndex.hpp"

#include "src/logger/CLogger.hpp"

class CBaseComponent;

class CEntity final : public std::enable_shared_from_this< CEntity >
{
	friend class CScene;

public:
	explicit CEntity( const std::string &name, const u16 sceneId );
	~CEntity();

	const std::string &Name() const;

	template< typename T, typename... Args >
	void Add( Args... args )
	{
		if( m_components[ T::Index ] != nullptr )
		{
			logWARNING( "entity '{0}' with id '{1}' already has a component of type '{2}'", m_name, Id, typeid( T ).name() );
		}
		else
		{
			m_components[ T::Index ] = std::make_shared< T >( shared_from_this(), args... );
		}
	};

	template< typename T >
	void Remove()
	{
		if( !HasComponents< T >() )
		{
			logWARNING( "entity '{0}' with id '{1}' does not have a component of type '{2}'", m_name, Id, typeid( T ).name() );
		}
		else
		{
			m_components[ T::Index ] = nullptr;
		}
	};

	template< typename T >
	std::shared_ptr< T > Get() const
	{
		const auto component = m_components[ T::Index ];

		if( nullptr == component )
		{
			logWARNING( "entity '{0}' with id '{1}' does not have a component of type '{2}'", m_name, Id, typeid( T ).name() );

			return( nullptr );
		}
		else
		{
			return( std::static_pointer_cast< T >( component ) );
		}
	};

	template < typename T >
	bool HasComponents() const
	{
		if( nullptr == m_components[ T::Index ] )
		{
			return( false );
		}
		else
		{
			return( true );
		}
	};

	template < typename First, typename Second, typename ... Rest >
	bool HasComponents() const
	{
		return( HasComponents< First >() && HasComponents< Second, Rest... >() );
	};

	const u32 Id = ++s_lastId;

	CTransform Transform;

private:
	std::array< std::shared_ptr< CBaseComponent >, static_cast< u16 >( EComponentIndex::MAX) > m_components;

	const std::string m_name;

	const u16 m_sceneId;

	static u32 s_lastId;
};
