#pragma once

#include "CInput.hpp"

#include "src/audio/CAudio.hpp"

#include "src/renderer/CRenderer.hpp"

#include "src/resource/CResources.hpp"

class CEngineInterface final
{
public:
	CEngineInterface( const CSettings &settings, const CFileSystem &filesystem );
	~CEngineInterface() {};

	CResources Resources;

	CInput		Input;
	CRenderer	Renderer;
	CAudio		Audio;

	struct
	{
		u64 frameTime;
	} Stats;

private:
	CEngineInterface( const CEngineInterface &rhs ) = delete;
	CEngineInterface& operator = ( const CEngineInterface &rhs ) = delete;
};
