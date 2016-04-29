#ifndef CSYSTEMMANAGER_HPP
#define CSYSTEMMANAGER_HPP

#include <vector>

#include "csystem.hpp"

class CSystemManager
{
public:
	~CSystemManager();

	template <typename T>
	void AddSystem()
	{
		T::systemID = m_systems.size();
		m_systems.emplace_back( new T() );
	}

	template <typename T>
	T* GetSystem()
	{
		return( static_cast<T*>( m_systems[ T::systemID ] ) );
	}

	void Update( const double dt )
	{
		for( CSystem* system : m_systems )
		{
			system->Update( dt );
		}
	}

private:
  std::vector< CSystem* > m_systems;
};

#endif // CSYSTEMMANAGER_HPP
