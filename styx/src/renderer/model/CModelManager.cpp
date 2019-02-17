#include "CModelManager.hpp"

#include "src/logger/CLogger.hpp"

CModelManager::CModelManager()
{
	logINFO( "model manager was initialized" );
}

CModelManager::~CModelManager()
{
	logINFO( "model manager is shutting down" );
}
