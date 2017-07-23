#ifndef CENGINEINTERFACE_HPP
#define CENGINEINTERFACE_HPP

#include "CInput.hpp"
#include "CTimer.hpp"

#include "src/engine/sound/CSoundManager.hpp"

#include "src/engine/renderer/CRenderer.hpp"

class CEngineInterface final
{
public:
	CEngineInterface( const CSettings &settings, const CFileSystem &filesystem );
	~CEngineInterface();

	CInput			Input;
	CRenderer		Renderer;
	CSoundManager	SoundManager;
	CTimer			GlobalTimer;

private:
	CEngineInterface( const CEngineInterface &rhs ) = delete;
	CEngineInterface& operator = ( const CEngineInterface &rhs ) = delete;
};

#endif // CENGINEINTERFACE_HPP
