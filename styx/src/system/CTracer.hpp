#pragma once

#include <unordered_map>
#include <chrono>
#include <tuple>
#include <functional>

#include "src/core/Types.hpp"

class CTracer final
{
public:
	CTracer()
	{
		m_traces.reserve( 50 );
	}

	class Element
	{
		friend class CTracer;

	public:
		void Stop()
		{
			if( onDestroy )
			{
				onDestroy( *this );
				onDestroy = nullptr;
			}
		}

	private:
		Element( const std::string &name ) :
			Name { name },
			Start { std::chrono::high_resolution_clock::now() }
		{}

		const std::string Name;
		const std::chrono::high_resolution_clock::time_point Start;

		std::function<void( const Element &element )>	onDestroy;
	};

	[[nodiscard]] CTracer::Element Start( const std::string &name )
	{
		Element element( name );

		element.onDestroy = [ this ]( const Element &element )
		{
			m_traces[ element.Name ] = ( std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - element.Start ).count() ) / 1000.0f;
		};

		return element;
	}

	const auto &Elements() const
	{
		return( m_traces );
	}

private:
	std::unordered_map<std::string, f16>	m_traces;
};
