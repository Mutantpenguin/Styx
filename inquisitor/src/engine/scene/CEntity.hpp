#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>
#include <memory>

#include "src/engine/scene/CTransform.hpp"

#include "src/engine/scene/components/EComponentIndex.hpp"

#include "src/engine/logger/CLogger.hpp"

class CBaseComponent;

class CEntity final : public std::enable_shared_from_this< CEntity >
{
	friend class CScene;

public:
	explicit CEntity( const std::string &name, const std::uint16_t sceneId );
	~CEntity();

	const std::string &Name( void ) const;

	template< typename T, typename... Args >
	std::shared_ptr< T > Add( Args... args )
	{
		if( m_components[ T::Index ] != nullptr )
		{
			logWARNING( "entity '{0}' with id '{1}' already has a component of type '{2}'", m_name, Id, typeid( T ).name() );

			return( nullptr );
		}
		else
		{
			auto component = std::make_shared< T >( shared_from_this(), args... );
			m_components[ T::Index ] = component;

			return( component );
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

	const std::uint32_t Id = ++s_lastId;

	CTransform Transform;

private:
	std::array< std::shared_ptr< CBaseComponent >, static_cast< std::uint16_t >( EComponentIndex::MAX) > m_components;

	const std::string m_name;

	const std::uint16_t m_sceneId;

	static std::uint32_t s_lastId;
};

#endif // COBJECT_HPP
