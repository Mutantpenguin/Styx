#include "csystemmanager.hpp"

CSystemManager::~CSystemManager()
{
	for( CSystem* system : m_systems )
	{
		delete system;
		system = nullptr;
	}
}
