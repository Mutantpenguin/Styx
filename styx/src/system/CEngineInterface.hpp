#pragma once

#include "CInput.hpp"

#include "src/audio/CAudio.hpp"

#include "src/renderer/CRenderer.hpp"

#include "src/resource/CResourceCacheManager.hpp"

class CEngineInterface final
{
public:
	CEngineInterface( const CSettings &settings, const CFileSystem &filesystem );
	~CEngineInterface() {};

	CResourceCacheManager ResourceCacheManager;

	CInput		Input;
	CRenderer	Renderer;
	CAudio		Audio;

private:
	CEngineInterface( const CEngineInterface &rhs ) = delete;
	CEngineInterface& operator = ( const CEngineInterface &rhs ) = delete;
};
